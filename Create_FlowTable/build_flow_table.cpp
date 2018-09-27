//==================================================================================================
//  NAME:: build_flow_table										
//                                                              
//  DESCRIPTION                                                 
//		build flow table                                       
//===================================================================================================
#include <iostream>
#include <fstream>
#include "blender.h"
#include "file_io.h"

using namespace std;

int build_flow_table(struct flow_struct *flow_table, double *dem, double *slope, int *patch,
	int *stream, int *roads, double *flna, int maxr, int maxc, int f_flag, int sc_flag, double cell)
{
 	// local variable declarations
	int num_patches;
	int inx;
	int r,c,pch;

 	// local function definitions
	void	zero_flow_table(struct flow_struct *,int,int);
	int		find_patch();
	int		check_neighbours();

	num_patches = 0;
	zero_flow_table(flow_table, maxr, maxc);
	
	for (r=0; r< maxr; r++){
		for (c=0; c< maxc; c++){
			inx = r*maxc+c;
			if (patch[inx] == -99999) {
				cout << "error in patch file use of -99999 as a patch label not allowed" << endl;
				exit(1);
			}

			// ignore areas outside the basin
			if ( patch[inx] > 0 ) {
				pch = find_patch(num_patches, flow_table, patch[inx]);

				if (pch == 0) {
					num_patches += 1;
					pch = num_patches;
				}
				//printf("pch inx and patch[inx] is %d %d %d",pch,inx,patch[inx]);
				//getchar();

				flow_table[pch].patchID = patch[inx];
				flow_table[pch].area += 1;
				flow_table[pch].x += ( double ) (1.0 * c)*cell*(maxr-r-1); //modified by guoping
				flow_table[pch].y += ( double ) (1.0 * r)*cell*(maxc-c-1); //modified by guoping
				flow_table[pch].z += ( double ) (dem[inx]);
				
				//flow_table[pch].K += ( double ) (1.0 * K[inx]);
					
				if (sc_flag == 1)
					flow_table[pch].internal_slope += ( double ) (1.0 * slope[inx]* DtoR );
				
				if (roads[inx] >= 1)
					flow_table[pch].land = 2;
				if (stream[inx] >= 1)
					flow_table[pch].land = 1;

			
				if (f_flag)
					flow_table[pch].flna += ( double ) (1.0 * flna[inx]);
				else
					flow_table[pch].flna = 0.0;

				//flow_table[pch].m_par += m_par[inx];
				flow_table[pch].num_adjacent += check_neighbours(r,c, patch,dem, stream,
								&flow_table[pch],
								flow_table[pch].num_adjacent,
								maxr, maxc, sc_flag, cell);
				//printf("\n neighbours %d %d \n",patch[inx],flow_table[pch].num_adjacent);
				//getchar();
			} 
		}		
	}
	std::cout<<"The number of patches are "<<num_patches<<std::endl;
	
	return num_patches;
}


