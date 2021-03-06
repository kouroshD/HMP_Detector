/*
 * HRI_HMP_Class.cpp
 *
 *  Created on: June 14, 2016
 *      Author: Kourosh Darvish
 */

#include "HRI_HMP_Class.hpp"

HRI_HMP_Class::HRI_HMP_Class() {

	hri_hmp_flag	=true;
	for (int ii=0;ii<5;ii++)
	{
		parameterHMP[ii]=="0";
//		parameterHMP2[ii]=0;
	}

	sub_hri_hmp	= nh.subscribe("HMPCommand", 1, &HRI_HMP_Class::Callback_hri_hmp, this);
	pub_HMP_cmnd	=nh.advertise<std_msgs::String>("HMPAck",1);

}

//	HMP
void HRI_HMP_Class::Callback_hri_hmp(const std_msgs::String::ConstPtr& msg1) {
	
	ROS_INFO("I received Initialization Message from API(hri) ...");
	string MSG=msg1-> data.c_str();
	//string parameterHMP[4];
	istringstream ss (MSG);
	copy(
		istream_iterator <string>(ss),
		istream_iterator <string> (),
		parameterHMP);

	//cout<<"I heard this msg in HMP from hri: \t";
	for (int jj=0; jj<5;jj++){
		//cout<<"parameterHMP["<<jj<<"]: "<<parameterHMP[jj]<<" \t";
	//cout<<endl;
	}

	if (parameterHMP[0]=="0")
	{
		cout<<"it is the \"get\" command!"<<endl;
		hri_hmp_flag	=false;

	}
	else if (parameterHMP[0]=="1")
	{
		cout<<"it is the \"set\" command!"<<endl;
		hri_hmp_flag	=false;
	}
	else 
		cout<<"it is Unreadable! "<<endl<<">> *****>>>> Send the command again"<<endl;

}

void HRI_HMP_Class::hri_hmp_process(void){

	//cout<<"I came to hri hmp initialization of actions!" <<endl;

	if (parameterHMP[0]=="0")
	{
		parameterHMP[0]="0";
		parameterHMP[1]="PickUp";
		parameterHMP[2]="Screwing";
		parameterHMP[3]="PutDown";
		parameterHMP[4]="ScrewingInitial";
//		parameterHMP[5]="standing";

	}
	else if (parameterHMP[0]=="1")
	{
		cout<<"it is the \"set\" command!"<<endl;
	}

}

void HRI_HMP_Class::publish_hri_hmp(void){

	//cout<<"I came to hri-hmp publish!" <<endl;

	std_msgs::String msg_HMPPar;
	std::stringstream ss_HMPPar;
	//cout<<"parameterHMP[ii]:"<<endl;
	for (int ii=0; ii< 5; ii++) {
		ss_HMPPar<<parameterHMP[ii]<<" ";
	}
//	cout<<endl;
	msg_HMPPar.data=ss_HMPPar.str();
	ROS_INFO("HMP Initialized ...");
	pub_HMP_cmnd.publish(msg_HMPPar);
	hri_hmp_flag	=true;
}


