__kernel void
copy_kern(
	int n,
	__global float4* b,
	__global float4* a
)
{
	int gti = get_global_id(0);

		b[gti] = a[gti];

}

 __kernel void
nbody_kern(
	int n,
	float dt,
	float eps,
	__global float4* pp,
	__global float4* vv,
	__global float4* ppo,
	__local float4* pblock
)
{
	const float4 zero4 = (float4){0.0f,0.0f,0.0f,0.0f};
	const float4 invtwo4 = (float4){0.5f,0.5f,0.5f,0.5f};
	const float4 dt4 = (float4){dt,dt,dt,0.0f};

//	int gti = 2*get_global_id(0);
	int gti = get_global_id(0);

	int ti = get_local_id(0);

	int nt = get_local_size(0);
//	int nb = 2*n/nt;
	int nb = n/nt;

	float4 p0 = ppo[gti+0];

	float4 a0 = zero4;

	int ib,i;

	// loop over blocks 

	for(ib=0;ib<nb;ib++) {

		prefetch(ppo,64);

		// copy to local memory 

		int gci = ib*nt+ti;

     	pblock[ti] = ppo[gci];

		barrier(CLK_LOCAL_MEM_FENCE);


		// loop within block accumulating acceleration of particles 

		for(i=0;i<nt;i+=8) {

			float4 p2 = pblock[i];
			float4 p3 = pblock[i+1];
			float4 p4 = pblock[i+2];
			float4 p5 = pblock[i+3];

			float4 p6 = pblock[i+4];
			float4 p7 = pblock[i+5];
			float4 p8 = pblock[i+6];
			float4 p9 = pblock[i+7];


			float4 dp = p2 - p0;	
			float invr = 1/ sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;


			dp = p3 - p0;	
			invr = 1/ sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;



			dp = p4 - p0;	
			invr = 1 / sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;


			dp = p5 - p0;	
			invr = 1/ sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;


			dp = p6 - p0;	
			invr = 1 /sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;


			dp = p7 - p0;	
			invr = 1/sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;


			dp = p8 - p0;	
			invr = 1/sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;


			dp = p9 - p0;	
			invr = 1/sqrt(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z + eps);
			a0 += (p2.w * invr*invr*invr)*dp;


		}

		barrier(CLK_LOCAL_MEM_FENCE);


	}

	// update position and velocity

	float4 v0 = vv[gti+0];
   p0 += dt4*v0 + invtwo4*dt4*dt4*a0;
   v0 += dt4*a0;
	pp[gti+0] = p0;
	vv[gti+0] = v0;

	return;

}
