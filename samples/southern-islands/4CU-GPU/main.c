/*
 * main.c
 *
 *  Created on: May 25, 2012
 *      Author: Amir Kavyan Ziabari
 */

#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>


#define MAX_SOURCE_SIZE (0x100000)


int main()
{
	//first we have to get the platform we have in hand
	cl_int ret;
	cl_platform_id platform = NULL;
	cl_uint num_platforms;
	cl_uint num_entries = 1;

	ret = clGetPlatformIDs(num_entries, &platform, &num_platforms);

	//Error check
	if (ret != CL_SUCCESS)
		printf("Error: in getting the platform IDs \n");
	else
		printf("The platform number is :%d \n", num_platforms);


	//get the device we want
	cl_device_id devices = NULL;
	cl_uint num_devices;
	ret = clGetDeviceIDs (platform, CL_DEVICE_TYPE_GPU, num_entries, &devices, &num_devices);

	if (ret != CL_SUCCESS)	printf("Error: in getting the Device IDs \n");
	else	printf("The device id is :%d \n", num_devices);

	//*NOTE: You can use clGetDeviceInfo to get some info on the device

	// creating context
	cl_context context;
	context = clCreateContext(NULL, num_devices, &devices, NULL, NULL, &ret);

	if (ret != CL_SUCCESS)
		printf("Error: in Creating Context \n");

	// creating command queue
	cl_command_queue cq;

	cq = clCreateCommandQueue(context, devices, 0, &ret);

	if (ret != CL_SUCCESS)
		printf("Error: in Creating command Queue \n");

	// Load the kernel source code into the array source_str
	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("matrix_mul.txt", "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load the kernel \n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose (fp);


	// creating a program with source
	cl_program program;
	fprintf (stderr, "%s",source_str);
	program = clCreateProgramWithSource(context, 1, (const char **) &source_str,
						 (const size_t *) &source_size, &ret);

	if (ret != CL_SUCCESS)	printf("Error: in Creating The program \n");

	//Building the OpenCL program
	ret = clBuildProgram(program, 1, &devices, NULL, NULL, NULL);

	if (ret != CL_SUCCESS)	printf("Error: in Building The program \n");

	//creating the Kernel
	cl_kernel kernel;
	kernel = clCreateKernel(program, "matrix_mul", &ret);

	if (ret != CL_SUCCESS)	printf("Error: in Creating The Kernel \n");

	/* OpenCL buffers
	 * i) creating the buffer in the HOST,
	 * ii) initiating source buffer in host
	 * iii) allocating source buffer in GPU
	 * iv) copy source buffer into GPU */

	// i)
	size_t dim = 8;
	size_t ldim = 4;
	const size_t num_elem = dim*dim; //size of element
	cl_int *A_host = (cl_int*)malloc(sizeof(cl_int) * num_elem);
	cl_int *B_host = (cl_int*)malloc(sizeof(cl_int) * num_elem);
	cl_int *C_host = (cl_int*)malloc(sizeof(cl_int) * num_elem);

	// ii)

	cl_int i ;
	for (i = 0; i< num_elem; i++)
	{
		A_host[i] = i;
		B_host[i] = i;
	}

	// iii)
	cl_mem A_device ;
	cl_mem B_device ;
	cl_mem C_device ;
	A_device = clCreateBuffer(context, CL_MEM_READ_ONLY,
				num_elem*sizeof(cl_int), NULL, &ret);
	if (ret != CL_SUCCESS)	printf("Error: in allocating buffer A in GPU \n");

	B_device = clCreateBuffer(context, CL_MEM_READ_ONLY,
				num_elem*sizeof(cl_int), NULL, &ret);
	if (ret != CL_SUCCESS)	printf("Error: in allocating buffer B in GPU \n");

	C_device =  clCreateBuffer(context, CL_MEM_WRITE_ONLY,
				num_elem*sizeof(cl_int), NULL, &ret);
	if (ret != CL_SUCCESS)	printf("Error: in allocating buffer C in GPU \n");

	// iv)
	ret = clEnqueueWriteBuffer (cq, A_device, CL_TRUE, 0, num_elem *sizeof(cl_int),
				A_host, 0, NULL, NULL );

	if (ret != CL_SUCCESS)	printf("Error: in copying source buffer into GPU \n");

	ret = clEnqueueWriteBuffer (cq, B_device, CL_TRUE, 0, num_elem *sizeof(cl_int),
				B_host, 0, NULL, NULL );

	if (ret != CL_SUCCESS)	printf("Error: in copying source buffer into GPU \n");


	/* Launching the Kernel contains 3 steps
	 * 1) Setting the Arguments
	 * 2) Main Function for Launching the Kernel
	 * 3) Finishing the execution */

	// 1) setting the arguments
	ret = clSetKernelArg( kernel, 0, sizeof (cl_mem), &A_device); // 0 indicates the first argument
	if (ret != CL_SUCCESS)	printf("Error: setting the first argument \n");

	ret = clSetKernelArg( kernel, 1, sizeof (cl_mem), &B_device); // 1 indicates the second argument
	if (ret != CL_SUCCESS)	printf("Error: setting the second argument \n");

	ret = clSetKernelArg( kernel, 2, sizeof (cl_mem), &C_device); // 2 indicates the third argument
	if (ret != CL_SUCCESS)	printf("Error: setting the third argument \n");

	ret = clSetKernelArg( kernel, 3, sizeof (cl_int)* ldim*ldim, NULL); // 3 indicates the forth argument
	if (ret != CL_SUCCESS)	printf("Error: setting the forth argument \n");

	ret = clSetKernelArg( kernel, 4, sizeof (cl_int)* ldim*ldim, NULL); // 4 indicates the fifth argument
	if (ret != CL_SUCCESS)	printf("Error: setting the fifth argument \n");

	// 2) main function for launching the kernel
	cl_uint dimension = 2;
	size_t global_work_size[2] = {dim, dim};
	size_t local_work_size[2] = {ldim, ldim};
	ret = clEnqueueNDRangeKernel (cq, kernel, dimension , NULL, global_work_size, local_work_size,
										0, NULL, NULL);
	if (ret != CL_SUCCESS)	printf("Error: Launching Kernel \n");
	// 3) finish the execution
	ret = clFinish(cq);

	if (ret != CL_SUCCESS)	printf("Error: Finishing the execution \n");

	/* Obtain the result from GPU to the CPU */

	// retrieving the buffer
	ret = clEnqueueReadBuffer (cq, C_device, CL_TRUE, 0, num_elem * sizeof(cl_int),
								C_host, 0, NULL, NULL);
	if (ret != CL_SUCCESS)	printf("Error: retrieving DST buffer into CPU \n");

	//print results
    // Display the result to the screen
    int j = 0;
    for(i = 0; i < dim; i++)
	{
	for (j = 0; j < dim ; j++)
        	printf("A[%d.%d] = %d \t", A_host[i], A_host[j], A_host[i*dim+j]);
	printf("\n");
	}
	printf("\n--------------------------------------------------------\n");
    for(i = 0; i < dim; i++)
	{
	for (j = 0; j < dim ; j++)
        	printf("C[%d.%d] = %d \t", A_host[i], B_host[j], C_host[i*dim+j]);
	printf("\n");
	}
	

    return(0);
}

