#pragma once

#include "rule.h"

bool debug = false;
#define REGULAR_AMT 8
#define NONSTOP_AMT 1
#define INITIAL_VEHICLE_AMT 50
#define VEHICLE_TU_AMT 5
#define SIM_TU_AMT 1200

struct CONTROL
{
	int regular_tk_wdw_amount, nonstop_tk_wdw_amount;
	int initial_vehicle_amount, vehicle_per_time_unity;
	int simulation_time;	
};

using namespace std;

void prog_data(CONTROL& control)
{
	cout << "QUANTIDADE DE GUICHÊS COMUNS: ";
	control.regular_tk_wdw_amount = REGULAR_AMT;
	cout << control.regular_tk_wdw_amount << endl;
	cout << "QUANTIDADE DE GUICHÊS SEM PARAR: ";
	control.nonstop_tk_wdw_amount = NONSTOP_AMT;
	cout << control.nonstop_tk_wdw_amount << endl;
	cout << "CARGA INICIAL DE CARROS: ";
	control.initial_vehicle_amount = INITIAL_VEHICLE_AMT;
	cout << control.initial_vehicle_amount << endl;
	cout << "QUANTIDADE DE ENTRADA DE VEÍCULOS POR UNIDADE DE TEMPO: ";
	control.vehicle_per_time_unity = VEHICLE_TU_AMT;
	cout << control.vehicle_per_time_unity << endl;
	cout << "QUANTIDADE DE UNIDADES DE TEMPO A SER SIMULADA: ";
	control.simulation_time = SIM_TU_AMT;
	cout << control.simulation_time << endl;
	control.simulation_time = control.simulation_time * TIME_UNITY;
}

void take_data(CONTROL& control)
{
	cout << "QUANTIDADE DE GUICHÊS COMUNS: ";
	cin >> control.regular_tk_wdw_amount;
	cout << "QUANTIDADE DE GUICHÊS SEM PARAR: ";
	cin >> control.nonstop_tk_wdw_amount;
	cout << "CARGA INICIAL DE CARROS: ";
	cin >> control.initial_vehicle_amount;
	cout << "QUANTIDADE DE ENTRADA DE VEÍCULOS POR UNIDADE DE TEMPO: ";
	cin >> control.vehicle_per_time_unity;
	cout << "QUANTIDADE DE UNIDADES DE TEMPO A SER SIMULADA: ";
	cin >> control.simulation_time;
	control.simulation_time = control.simulation_time * TIME_UNITY;
}