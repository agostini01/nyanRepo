#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#include <CL/cl.h>

#define frand() (rand()/(cl_float)RAND_MAX)

#define __index(i,e) (4*(i)+(e))
#define __index_x(i) __index(i,0)
#define __index_y(i) __index(i,1)
#define __index_z(i) __index(i,2)
#define __index_m(i) __index(i,3)

cl_context context;
cl_platform_id platform;
cl_device_id* device_id;
cl_command_queue commands;
cl_program program;
cl_kernel kernel, copy_kernel;

int nstep = 100;
/* MUST divide the value of nstep without remainder */
int nburst = 50;
/* MUST be a nice power of two for simplicity */
int nparticle = 128;

void nbody_init( int n, cl_float* pp, cl_float* vv );
bool setDevice( int , const char* );
bool setData(cl_float* pos1, cl_float* pos2, cl_float* vel);
using namespace std;
int main(int argc, char** argv)
{


	cl_float* pos1 = (cl_float*)malloc(4*sizeof(cl_float)*nparticle);
	cl_float* pos2 = (cl_float*)malloc(4*sizeof(cl_float)*nparticle);
	cl_float* vel = (cl_float*)malloc(4*sizeof(cl_float)*nparticle);

	nbody_init(nparticle,pos1,vel);
	
	if (setDevice(CL_DEVICE_TYPE_GPU, "nbody_kern.cl"))
	{
		
		for (int step = 0; step < nstep ; step +=nburst)
		{
			bool check = setData(pos1, pos2, vel);	
			if (check != true)
			{
				fprintf(stderr,"something went wrong\n");
				break;
			}
		}
	}

	free(pos1);
	free(pos2);
	free(vel);

	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseKernel(copy_kernel);
	clReleaseCommandQueue(commands);
	clReleaseContext(context);
	return 0;
}


void nbody_init( int n, cl_float* pp, cl_float* vv )
{
	int i;

	printf("nbody_init %d\n",n); fflush(stdout);

	cl_float a1,a2,a3,a4,a5,a6,a7,a8;
	cl_float cmr[3];
	cl_float cmrdot[3];

	cl_float alphas = 2.0;
	cl_float body1 = 5.0;
	cl_float bodyn = 1.0;

	cl_float twopi = 6.283185307;

	cl_float alpha1 = alphas - 1.0;
	cl_float fm1 = 1.0/pow(body1,alpha1);
	cl_float fmn = (fm1 - 1.0/pow(bodyn,alpha1))/((cl_float)n - 1.0);
	cl_float zmass = 0.0;
	cl_float coef = 1.0/alpha1;

	for(i=0;i<n;i++) {
		cl_float fmi = fm1 - (cl_float)(i-1)*fmn;
		pp[__index_m(i)] = 1.0/pow(fmi,coef);
		zmass += pp[__index_m(i)];
	}


	cl_float zmbar1 = zmass/(cl_float)n;
	for(i=0;i<n;i++) pp[__index_m(i)] /= zmbar1;
	zmass = (cl_float)n;

	cmr[0] = cmr[1] = cmr[2] = 0.0f;
	cmrdot[0] = cmrdot[1] = cmrdot[2] = 0.0f;

	cl_float ri;
	for(i=0;i<n;i++) {

		do {
			a1 = frand();
			ri = 1.0/sqrt((pow(a1,(-0.6666667))-1.0));
		} while (ri > 10.0);

		a2 = frand();
		a3 = frand();
		pp[__index_z(i)] = (1.0 - 2.0*a2)*ri;
		pp[__index_x(i)] = sqrt(ri*ri 
			- pp[__index_z(i)]*pp[__index_z(i)])*cos(twopi*a3);
		pp[__index_y(i)] = sqrt(ri*ri 
			- pp[__index_z(i)]*pp[__index_z(i)])*sin(twopi*a3);

		do {
			a4 = frand();
			a5 = frand();
			a6 = a4*a4*pow((1.0-a4*a4),3.5);
		} while (0.1*a5 > a6);

		a8 = a4*sqrt(2.0)/pow((1.0 + ri*ri),0.25);
		a6 = frand();
		a7 = frand();
	
		vv[__index_z(i)] = (1.0 - 2.0*a6)*a8;
		vv[__index_x(i)] = sqrt(a8*a8 
			- vv[__index_z(i)]*vv[__index_z(i)])*cos(twopi*a7);
		vv[__index_y(i)] = sqrt(a8*a8 
			- vv[__index_z(i)]*vv[__index_z(i)])*sin(twopi*a7);
		vv[__index_m(i)] = 0.0f;

		cmr[0] += pp[__index_m(i)] * pp[__index_x(i)];
		cmr[1] += pp[__index_m(i)] * pp[__index_y(i)];
		cmr[2] += pp[__index_m(i)] * pp[__index_z(i)];
		cmrdot[0] += pp[__index_m(i)] * pp[__index_x(i)];
		cmrdot[1] += pp[__index_m(i)] * pp[__index_y(i)];
		cmrdot[2] += pp[__index_m(i)] * pp[__index_z(i)];

	}

	a1 = 1.5*twopi/16.0;
	a2 = sqrt(zmass/a1);
	for(i=0;i<n;i++) {

		pp[__index_x(i)] -= cmr[0]/zmass;
		pp[__index_y(i)] -= cmr[1]/zmass;
		pp[__index_z(i)] -= cmr[2]/zmass;
		vv[__index_x(i)] -= cmrdot[0]/zmass;
		vv[__index_y(i)] -= cmrdot[1]/zmass;
		vv[__index_z(i)] -= cmrdot[2]/zmass;
		pp[__index_x(i)] *= a1;
		pp[__index_y(i)] *= a1;
		pp[__index_z(i)] *= a1;
		vv[__index_x(i)] *= a2;
		vv[__index_y(i)] *= a2;
		vv[__index_z(i)] *= a2;
	}


	cl_float ppmin = pp[0];	
	cl_float ppmax = pp[0];	
	for(i=0;i<n;i++) ppmin = (ppmin<pp[__index_x(i)])? ppmin:pp[__index_x(i)];
	for(i=0;i<n;i++) ppmin = (ppmin<pp[__index_y(i)])? ppmin:pp[__index_y(i)];
	for(i=0;i<n;i++) ppmin = (ppmin<pp[__index_z(i)])? ppmin:pp[__index_z(i)];
	for(i=0;i<n;i++) ppmax = (ppmax>pp[__index_x(i)])? ppmax:pp[__index_x(i)];
	for(i=0;i<n;i++) ppmax = (ppmax>pp[__index_y(i)])? ppmax:pp[__index_y(i)];
	for(i=0;i<n;i++) ppmax = (ppmax>pp[__index_z(i)])? ppmax:pp[__index_z(i)];
}

bool setDevice(int device_type, const char* file_location)
{
	cl_int err;
	err = clGetPlatformIDs(1, &platform, NULL);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to find a platform!" << endl;
		return false;
	}

	// Get a device of the appropriate type
	// compute device id
	device_id = (cl_device_id*)malloc(sizeof(cl_device_id)); 

	err = clGetDeviceIDs(platform, device_type, 1, device_id, NULL);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to create a device group!" << endl;
		return false;
	}

	context = clCreateContext(0, 1, device_id, NULL, NULL, &err);
	if (!context) 
	{
		cerr << "Error: Failed to create a compute context!" << endl;
		return false;
	}

	commands = clCreateCommandQueue(context, *device_id, 0, &err);
	if (!commands) 
	{
		cerr << "Error: Failed to create a command commands!" 
		<< endl;
		return false;
	}
  
	FILE *fp;
	char *source_str;
	size_t source_size;
 
	fp = fopen(file_location, "r");
	if (!fp) 
	{
		fprintf(stderr, "Failed to load kernel.\n");
		return false;
	}
	source_str = (char*)malloc(0x100000);
	source_size = fread( source_str, 1, 0x100000, fp);
	fclose( fp );

	program = clCreateProgramWithSource(context, 1,(const char **) 
		&source_str, (const size_t *) &source_size, &err);
	if (!program) 
	{
		cerr << "Error: Failed to create compute program!" << endl;
		return false;
	}
    
	err = clBuildProgram(program, 1 , device_id, NULL, NULL, NULL);
	if (err != CL_SUCCESS) 
	{
		size_t len;
		char buffer[2048];    
		cerr << "Error: Failed to build program executable!" << endl;
		clGetProgramBuildInfo(program, *device_id,
			CL_PROGRAM_BUILD_LOG,sizeof(buffer), buffer, &len);
		cerr << buffer << endl;
		return false;
	}
    
	kernel = clCreateKernel(program, "nbody_kern", &err);
	if (!kernel || err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to create compute kernel!" << endl;
		return false;
	}

	copy_kernel = clCreateKernel(program, "copy_kern", &err);
	if (!copy_kernel || err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to create compute kernel!" << endl;
		return false;
	}
	return true;
}

bool setData(cl_float* position,cl_float* position2, cl_float* velocity)
{
	float dt = 1e-4;
	float eps = 1e-2;
	/* chosen for ATI Radeon HD 5870 */
	size_t nthread = 64;
	cl_int err;

	cl_mem c_pos1 = clCreateBuffer(context, CL_MEM_READ_WRITE, 
			4*sizeof(cl_float)*nparticle, NULL, &err);
	cl_mem c_vel = clCreateBuffer(context, CL_MEM_READ_WRITE, 
			4*sizeof(cl_float)*nparticle, NULL, &err);
	cl_mem c_pos2 = clCreateBuffer(context, CL_MEM_READ_WRITE, 
			4*sizeof(cl_float)*nparticle, NULL, &err);

	if (err)
	{
		cerr << "error in cl_mem allocation" << endl;
	}


	err = clEnqueueWriteBuffer(commands, c_pos1, CL_TRUE, 0, 
			4*sizeof(cl_float)*nparticle, position, 0, 
			NULL, NULL);

	if (err != CL_SUCCESS) 
	{
		cerr << "Error: c_pos1 - Failed to write to source array!" 
			<< endl;
		return false;
	}

	err = clEnqueueWriteBuffer(commands, c_vel, CL_TRUE, 0, 
			4*sizeof(cl_float)*nparticle, velocity, 0, 
			NULL, NULL);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: c_vel - Failed to write to source array!" 
			<< endl;
		return false;
	}

	err = clEnqueueWriteBuffer(commands, c_pos2, CL_TRUE, 0, 
			4*sizeof(cl_float)*nparticle, position2, 
			0, NULL, NULL);

	if (err != CL_SUCCESS) 
	{
		cerr << "Error: c_posFailed to write to source array!" 
			<< endl;
		return false;
	}

	int n = nparticle/2;
	err = clSetKernelArg(kernel, 0, sizeof(int), &n);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set kernel argument 0! " 
			<< err << endl;
		return false;
	}  

	err = clSetKernelArg(kernel, 1, sizeof(float), &dt);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set kernel argument 1! "	
			<< err << endl;
		return false;
	}  

	err = clSetKernelArg(kernel, 2, sizeof(float), &eps);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set kernel argument 2! " 
			<< err << endl;
		return false;
	}  

	err = clSetKernelArg(kernel, 4, sizeof(cl_mem), &c_vel);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set kernel argument 4! " 
			<< err << endl;
		return false;
	}  
	
	err = clSetKernelArg(kernel, 6, sizeof(cl_float)*4*nthread, NULL);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set kernel argument 6! " 
			<< err << endl;
		return false;
	}  

	err = clSetKernelArg(copy_kernel, 0, sizeof(int), &nparticle);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set copy kernel argument 0! " 
			<< err << endl;
		return false;
	}
	
	err = clSetKernelArg(copy_kernel, 1, sizeof(cl_mem), &c_pos1);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set copy kernel argument 1! " 
			<< err << endl;
		return false;
	}

	err = clSetKernelArg(copy_kernel, 2, sizeof(cl_mem), &c_pos2);
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: Failed to set copy kernel argument 2! " 
			<< err << endl;
		return false;
	}

	for (int burst = 0; burst < nburst; burst++)
	{
		err = clSetKernelArg(kernel, 3, sizeof(cl_mem), &c_pos2);
		if (err != CL_SUCCESS) 
		{
			cerr << "Error: Failed to set kernel argument 3! " 
				<< err << endl;
		return false;
		}
	
		err = clSetKernelArg(kernel, 5, sizeof(cl_mem), &c_pos1);
		if (err != CL_SUCCESS) 
		{
			cerr << "Error: Failed to set kernel argument 5! " 
				<< err << endl;
		return false;
		}
	
		size_t global = n;
		err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, 
			&global, &nthread ,0, NULL, NULL);
		if (err != CL_SUCCESS) 
		{
			cerr << "Error: kernel - Failed to execute kernel!" 
				<< err << endl;
			return false;
		}
		
/*		err = clEnqueueCopyBuffer(commands, c_pos2, c_pos1, 0, 0,
			4*sizeof(cl_float)*nparticle, 0, NULL, NULL);
		if (err != CL_SUCCESS)
		{
			cerr << "Error: buffer copy!" << endl;
			return false;
		} */
		err = clEnqueueNDRangeKernel(commands, copy_kernel, 1, NULL, 
			&global, &nthread ,0, NULL, NULL);
		if (err != CL_SUCCESS) 
		{
			cerr << "Error: cop_kernel - Failed to execute !" 
				<< endl;
			return false;
		}		
	}

	err = clEnqueueReadBuffer( commands, c_pos1 ,CL_TRUE, 
		0, nparticle * 4 * sizeof(float), position, 0, NULL, NULL ); 
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: c_pos1 - Failed to read output array! " 
			<<  err << endl;
		return false;
	}

	err = clEnqueueReadBuffer( commands, c_vel ,CL_TRUE, 
		0, nparticle * 4 * sizeof(float), velocity, 0, NULL, NULL ); 
	if (err != CL_SUCCESS) 
	{
		cerr << "Error: c_vel Failed to read output array! " 
			<<  err << endl;
		return false;
	}

	clFlush(commands);

	clReleaseMemObject(c_pos1);
	clReleaseMemObject(c_pos2);
	clReleaseMemObject(c_vel);
	
	return true;
}
