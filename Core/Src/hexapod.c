#include "hexapod.h"

float pos_leg_defaut[6][3] = {{9.546, 9.546, 14.6},
															{-9.546, 9.546, 15},
															{13.5, 0, 15},
															{-13.5, 0, 15},
															{9.546, -9.546, 15},
															{-9.546, -9.546, 14.6}};

theta theta_leg_1;
pos_leg pos_leg_1;
theta theta_leg_2;
pos_leg pos_leg_2;
theta theta_leg_3;
pos_leg pos_leg_3;
theta theta_leg_4;
pos_leg pos_leg_4;
theta theta_leg_5;
pos_leg pos_leg_5;
theta theta_leg_6;
pos_leg pos_leg_6;
	
theta theta_leg_1_last;
theta theta_leg_2_last;
theta theta_leg_3_last;
theta theta_leg_4_last;
theta theta_leg_5_last;
theta theta_leg_6_last;

pos_leg UPDATE_POS_LEG(float vx, float vy, float up_z, int LEG_ID, float TIME_PHASE)
{
	pos_leg pos_leg_tranf;
	pos_leg_tranf.x = pos_leg_defaut[LEG_ID][0] + vx*TIME_PHASE;
	pos_leg_tranf.y = pos_leg_defaut[LEG_ID][1] + vy*TIME_PHASE;
	pos_leg_tranf.z = pos_leg_defaut[LEG_ID][2] - up_z;
	return pos_leg_tranf;
}

pos_leg POS_DEFAUT(int LEG_ID)
{
	pos_leg pos_leg_tranf;
	pos_leg_tranf.x = pos_leg_defaut[LEG_ID][0];
	pos_leg_tranf.y = pos_leg_defaut[LEG_ID][1];
	pos_leg_tranf.z = pos_leg_defaut[LEG_ID][2];
	return pos_leg_tranf;
}

void TRIPPLE_GAIT(float vx, float vy, float up_z, float alpha)
{
	//LEG_1 LEG_4 LEG_5
	pos_leg_1 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_1, TIME_PHASE_T);
	pos_leg_4 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_4, TIME_PHASE_T);
	pos_leg_5 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_5, TIME_PHASE_T);
	//LEG_2 LEG_3 LEG_6
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, alpha, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, alpha, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, alpha, 0, 0, PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
		
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
		
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
		
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
		
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
		
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_2;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_3;
		
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
		
		//LEG_1 LEG_4 LEG_5
	pos_leg_1 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_1, TIME_PHASE_T);
	pos_leg_4 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_4, TIME_PHASE_T);
	pos_leg_5 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_5, TIME_PHASE_T);
	//LEG_2 LEG_3 LEG_6
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, alpha, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, alpha, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, alpha, 0, 0, PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
					
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
	
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
	
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
	
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
	
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_2;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_3;
	
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
		
	// phase 2
	//LEG_1 LEG_4 LEG_5
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	//LEG_2 LEG_3 LEG_6
	pos_leg_2 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_2, TIME_PHASE_T);
	pos_leg_3 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_3, TIME_PHASE_T);
	pos_leg_6 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_6, TIME_PHASE_T);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, alpha, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, alpha, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, alpha, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
		
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
		
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
		
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
		
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
		
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_2;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_3;
		
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
		
		//LEG_1 LEG_4 LEG_5
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	//LEG_2 LEG_3 LEG_6
	pos_leg_2 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_2, TIME_PHASE_T);
	pos_leg_3 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_3, TIME_PHASE_T);
	pos_leg_6 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_6, TIME_PHASE_T);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, alpha, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, alpha, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, alpha, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
		
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
	
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
	
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
	
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
	
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_2;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_3;
	
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
}

void RIPPLE_GAIT(float vx, float vy, float up_z, float alpha)
{
	//=================================PHASE 1===================================
	//LEG_1 LEG_4
	pos_leg_1 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_1, TIME_PHASE_R);
	pos_leg_4 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_4, TIME_PHASE_R);
	//LEG_3 LEG_6
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	//LEG_2 LEG_5
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, alpha, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, alpha, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/600,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/600,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/600);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/600,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/600,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/600);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/600,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/600,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/600);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/600,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/600,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/600);
			HAL_Delay(1);
		}
					
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
	
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.25;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.25;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.25;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.25;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.25;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.25;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.25;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.25;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.25;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.25;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.25;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.25;
	
	//LEG_1 LEG_4
	pos_leg_1 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_1, TIME_PHASE_R);
	pos_leg_4 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_4, TIME_PHASE_R);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, alpha, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, alpha, 0, 0, PI);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_4 = IK_LEG(pos_leg_4);
	
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/600,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/600,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/600);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/600,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/600,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/600);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/600,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/600,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/600);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/600,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/600,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/600);
			HAL_Delay(1);
		}
					
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
	
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.25;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.25;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.25;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.25;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.25;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.25;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.25;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.25;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.25;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.25;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.25;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.25;
	
	//=================================PHASE 2===================================
	//LEG_1 LEG_4
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	//LEG_3 LEG_6
	pos_leg_3 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_3, TIME_PHASE_R);
	pos_leg_6 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_6, TIME_PHASE_R);
	//LEG_2 LEG_5
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, alpha, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, alpha, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/600,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/600,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/600);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/600,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/600,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/600);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/600,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/600,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/600);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/600,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/600,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/600);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
		
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.25;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.25;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.25;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.25;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.25;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.25;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.25;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.25;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.25;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.25;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.25;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.25;
	
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_2;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_3;
	
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
	
	//LEG_3 LEG_6
	pos_leg_3 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_3, TIME_PHASE_R);
	pos_leg_6 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_6, TIME_PHASE_R);
	
	//quy doi he toa do
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, alpha, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, alpha, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/600,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/600,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/600);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/600,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/600,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/600);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/600,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/600,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/600);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/600,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/600,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/600);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
					
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.25;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.25;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.25;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.25;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.25;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.25;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.25;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.25;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.25;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.25;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.25;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.25;
	
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_2;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_3;
	
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
	
	//=================================PHASE 3===================================
	//LEG_1 LEG_4
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	//LEG_3 LEG_6
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	//LEG_2 LEG_5
	pos_leg_2 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_2, TIME_PHASE_R);
	pos_leg_5 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_5, TIME_PHASE_R);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, alpha, 0, 0, PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, alpha, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/600,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/600,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/600);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/600,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/600,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/600);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/600,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/600,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/600);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/600,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/600,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/600);
			HAL_Delay(1);
		}
		
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.25;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.25;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.25;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.25;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.25;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.25;
	
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
	
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.25;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.25;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.25;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.25;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.25;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.25;
	
	//LEG_2 LEG_5
	pos_leg_2 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_2, TIME_PHASE_R);
	pos_leg_5 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_5, TIME_PHASE_R);
	
	//quy doi he toa do
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, alpha, 0, 0, -3*PI/4);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, alpha, 0, 0, PI/4);
	
	//tinh theta
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_5 = IK_LEG(pos_leg_5);
	
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/600,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/600,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/600);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/600,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/600,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/600);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/600,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/600,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/600);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/600,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/600,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/600);
			HAL_Delay(1);
		}
					
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.25;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.25;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.25;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.25;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.25;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.25;
	
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
	
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.25;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.25;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.25;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.25;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.25;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.25;
}

void WAVE_GAIT(float vx, float vy, float up_z, float alpha)
{
	//=================================PHASE 1===================================
	//LEG_1
	pos_leg_1 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_1, TIME_PHASE_W);
	//LEG_2 LEG_3 LEG_4 LEG_5 LEG_6
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, alpha, 0, 0, -PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//LEG_1
	pos_leg_1 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_1, TIME_PHASE_W);
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, alpha, 0, 0, -PI/4);
	theta_leg_1 = IK_LEG(pos_leg_1);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/150,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/150,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/150);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1.theta_1;
	theta_leg_1_last.theta_2 = theta_leg_1.theta_2;
	theta_leg_1_last.theta_3 = theta_leg_1.theta_3;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//=================================PHASE 2===================================
	//LEG_3
	pos_leg_3 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_3, TIME_PHASE_W);
	//LEG_1 LEG_2 LEG_4 LEG_5 LEG_6
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, alpha, 0, 0, 0);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//LEG_3
	pos_leg_3 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_3, TIME_PHASE_W);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, alpha, 0, 0, 0);
	theta_leg_3 = IK_LEG(pos_leg_3);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/150,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/150,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/150);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3.theta_1;
	theta_leg_3_last.theta_2 = theta_leg_3.theta_2;
	theta_leg_3_last.theta_3 = theta_leg_3.theta_3;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//=================================PHASE 3===================================
	//LEG_5
	pos_leg_5 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_5, TIME_PHASE_W);
	//LEG_1 LEG_2 LEG_3 LEG_4 LEG_6
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, alpha, 0, 0, PI/4);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//LEG_5
	pos_leg_5 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_5, TIME_PHASE_W);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, alpha, 0, 0, PI/4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/150,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/150,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/150);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5.theta_1;
	theta_leg_5_last.theta_2 = theta_leg_5.theta_2;
	theta_leg_5_last.theta_3 = theta_leg_5.theta_3;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//=================================PHASE 4===================================
	//LEG_2
	pos_leg_2 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_2, TIME_PHASE_W);
	//LEG_1 LEG_3 LEG_4 LEG_5 LEG_6
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, alpha, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//LEG_2
	pos_leg_2 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_2, TIME_PHASE_W);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, alpha, 0, 0, -3*PI/4);
	theta_leg_2 = IK_LEG(pos_leg_2);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/150,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/150,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/150);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2.theta_1;
	theta_leg_2_last.theta_2 = theta_leg_2.theta_2;
	theta_leg_2_last.theta_3 = theta_leg_2.theta_3;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//=================================PHASE 5===================================
	//LEG_4
	pos_leg_4 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_4, TIME_PHASE_W);
	//LEG_1 LEG_2 LEG_3 LEG_5 LEG_6
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	pos_leg_6 = POS_DEFAUT(ID_LEG_6);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, alpha, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, 0, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//LEG_4
	pos_leg_4 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_4, TIME_PHASE_W);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, alpha, 0, 0, PI);
	theta_leg_4 = IK_LEG(pos_leg_4);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/150,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/150,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/150);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/1500,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/1500,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/1500);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4.theta_1;
	theta_leg_4_last.theta_2 = theta_leg_4.theta_2;
	theta_leg_4_last.theta_3 = theta_leg_4.theta_3;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*0.1;
	theta_leg_6_last.theta_2 = theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*0.1;
	theta_leg_6_last.theta_3 = theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*0.1;
	
	//=================================PHASE 6===================================
	//LEG_6
	pos_leg_6 = UPDATE_POS_LEG(vx/2, vy/2, up_z, ID_LEG_6, TIME_PHASE_W);
	//LEG_1 LEG_2 LEG_3 LEG_4 LEG_5
	pos_leg_1 = POS_DEFAUT(ID_LEG_1);
	pos_leg_2 = POS_DEFAUT(ID_LEG_2);
	pos_leg_3 = POS_DEFAUT(ID_LEG_3);
	pos_leg_4 = POS_DEFAUT(ID_LEG_4);
	pos_leg_5 = POS_DEFAUT(ID_LEG_5);
	
	//quy doi he toa do
	pos_leg_1 = BODY_TO_LEG(pos_leg_1, 0, 0, 0, -PI/4);
	pos_leg_2 = BODY_TO_LEG(pos_leg_2, 0, 0, 0, -3*PI/4);
	pos_leg_3 = BODY_TO_LEG(pos_leg_3, 0, 0, 0, 0);
	pos_leg_4 = BODY_TO_LEG(pos_leg_4, 0, 0, 0, PI);
	pos_leg_5 = BODY_TO_LEG(pos_leg_5, 0, 0, 0, PI/4);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, alpha, 0, 0, 3*PI/4);
	
	//tinh theta
	theta_leg_1 = IK_LEG(pos_leg_1);
	theta_leg_2 = IK_LEG(pos_leg_2);
	theta_leg_3 = IK_LEG(pos_leg_3);
	theta_leg_4 = IK_LEG(pos_leg_4);
	theta_leg_5 = IK_LEG(pos_leg_5);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
	//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
	
	//LEG_6
	pos_leg_6 = UPDATE_POS_LEG(vx, vy, 0, ID_LEG_6, TIME_PHASE_W);
	pos_leg_6 = BODY_TO_LEG(pos_leg_6, alpha, 0, 0, 3*PI/4);
	theta_leg_6 = IK_LEG(pos_leg_6);
	
//run
	for(int i=1; i<151; i++)
		{
			LEG_1(theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*i/1500,
						theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*i/1500,
						theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*i/1500);
			
			LEG_4(theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*i/1500,
						theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*i/1500,
						theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*i/1500);
			
			LEG_5(theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*i/1500,
						theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*i/1500,
						theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*i/1500);
			
			LEG_2(theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*i/1500,
						theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*i/1500,
						theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*i/1500);
			
			LEG_3(theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*i/1500,
						theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*i/1500,
						theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*i/1500);
			
			LEG_6(theta_leg_6_last.theta_1 + (theta_leg_6.theta_1 - theta_leg_6_last.theta_1)*i/150,
						theta_leg_6_last.theta_2 + (theta_leg_6.theta_2 - theta_leg_6_last.theta_2)*i/150,
						theta_leg_6_last.theta_3 + (theta_leg_6.theta_3 - theta_leg_6_last.theta_3)*i/150);
			HAL_Delay(1);
		}
				
	theta_leg_1_last.theta_1 = theta_leg_1_last.theta_1 + (theta_leg_1.theta_1 - theta_leg_1_last.theta_1)*0.1;
	theta_leg_1_last.theta_2 = theta_leg_1_last.theta_2 + (theta_leg_1.theta_2 - theta_leg_1_last.theta_2)*0.1;
	theta_leg_1_last.theta_3 = theta_leg_1_last.theta_3 + (theta_leg_1.theta_3 - theta_leg_1_last.theta_3)*0.1;
	
	theta_leg_2_last.theta_1 = theta_leg_2_last.theta_1 + (theta_leg_2.theta_1 - theta_leg_2_last.theta_1)*0.1;
	theta_leg_2_last.theta_2 = theta_leg_2_last.theta_2 + (theta_leg_2.theta_2 - theta_leg_2_last.theta_2)*0.1;
	theta_leg_2_last.theta_3 = theta_leg_2_last.theta_3 + (theta_leg_2.theta_3 - theta_leg_2_last.theta_3)*0.1;
	
	theta_leg_3_last.theta_1 = theta_leg_3_last.theta_1 + (theta_leg_3.theta_1 - theta_leg_3_last.theta_1)*0.1;
	theta_leg_3_last.theta_2 = theta_leg_3_last.theta_2 + (theta_leg_3.theta_2 - theta_leg_3_last.theta_2)*0.1;
	theta_leg_3_last.theta_3 = theta_leg_3_last.theta_3 + (theta_leg_3.theta_3 - theta_leg_3_last.theta_3)*0.1;
	
	theta_leg_4_last.theta_1 = theta_leg_4_last.theta_1 + (theta_leg_4.theta_1 - theta_leg_4_last.theta_1)*0.1;
	theta_leg_4_last.theta_2 = theta_leg_4_last.theta_2 + (theta_leg_4.theta_2 - theta_leg_4_last.theta_2)*0.1;
	theta_leg_4_last.theta_3 = theta_leg_4_last.theta_3 + (theta_leg_4.theta_3 - theta_leg_4_last.theta_3)*0.1;
	
	theta_leg_5_last.theta_1 = theta_leg_5_last.theta_1 + (theta_leg_5.theta_1 - theta_leg_5_last.theta_1)*0.1;
	theta_leg_5_last.theta_2 = theta_leg_5_last.theta_2 + (theta_leg_5.theta_2 - theta_leg_5_last.theta_2)*0.1;
	theta_leg_5_last.theta_3 = theta_leg_5_last.theta_3 + (theta_leg_5.theta_3 - theta_leg_5_last.theta_3)*0.1;
	
	theta_leg_6_last.theta_1 = theta_leg_6.theta_1;
	theta_leg_6_last.theta_2 = theta_leg_6.theta_2;
	theta_leg_6_last.theta_3 = theta_leg_6.theta_3;
}

void RUN_HEXAPOD(float vx, float vy, float up_z, float alpha, int8_t gait_type)
{
	//alpha = alpha + 0.1;
	if(gait_type == 0)
	{
		TRIPPLE_GAIT(0, 0, 0, 0);
	}
	else if(gait_type == 1)
	{
		alpha = alpha*TIME_PHASE_T/100 + 0.08;
		TRIPPLE_GAIT(vx, vy, up_z, alpha);
	}
	else if(gait_type == 2)
	{
		alpha = alpha*TIME_PHASE_R/100 + 0.08;
		RIPPLE_GAIT(vx, vy, up_z, alpha);
	}
	else if(gait_type == 3)
	{
		alpha = alpha*TIME_PHASE_W/100 + 0.08;
		WAVE_GAIT(vx, vy, up_z, alpha);
	}
}