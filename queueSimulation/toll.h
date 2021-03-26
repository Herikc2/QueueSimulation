#pragma once

#include "queue.h"

#define TIME_UNITY 50

using namespace std;

struct VEHICLE
{
	TIMER timer;
	int time;
	int toll;
};

VEHICLE new_vehicle(int time, int toll)
{
	VEHICLE vehicle;
	vehicle.time = time;
	vehicle.toll = toll;
	vehicle.timer = new_timer();
	return vehicle;
}

struct TICKET_WINDOW
{
	QUEUE<VEHICLE> vehicle_queue;
	int accumulator;
};

struct TOLL
{
	int max_regular;
	int max_nonstop;
	int regular_accumulator;
	int nonstop_accumulator;
	int general_accumulator;
	TICKET_WINDOW *regular;
	TICKET_WINDOW *nonstop;
};

TICKET_WINDOW new_ticket_window()
{
	TICKET_WINDOW ticket_window;
	initialize_queue(ticket_window.vehicle_queue);
	ticket_window.accumulator = 0;
	return ticket_window;
}

TOLL new_toll(int MAX_REGULAR, int MAX_NONSTOP)
{
	TOLL toll;

	toll.general_accumulator = 0;
	toll.nonstop_accumulator = 0;
	toll.regular_accumulator = 0;
	toll.max_regular = MAX_REGULAR;
	toll.regular = new TICKET_WINDOW[MAX_REGULAR];
	toll.max_nonstop = MAX_NONSTOP;
	toll.nonstop = new TICKET_WINDOW[MAX_NONSTOP];

	for (size_t i = 0; i < (unsigned)MAX_REGULAR; i++)
		toll.regular[i] = new_ticket_window();

	for (size_t i = 0; i < (unsigned)MAX_NONSTOP; i++)
		toll.nonstop[i] = new_ticket_window();

	return toll;
}

void print_data(VEHICLE vehicle)
{
	cout << "Veículo" << endl;
}

void counter(TOLL& toll)
{
	for (size_t i = 0; i < toll.max_regular; i++) {
		toll.regular[i].accumulator += queue_data_amount(toll.regular[i].vehicle_queue);
		toll.regular_accumulator+= queue_data_amount(toll.regular[i].vehicle_queue);
		toll.general_accumulator += queue_data_amount(toll.regular[i].vehicle_queue);
	}
	for (size_t i = 0; i < toll.max_nonstop; i++) {
		toll.nonstop[i].accumulator += queue_data_amount(toll.nonstop[i].vehicle_queue);
		toll.nonstop_accumulator += queue_data_amount(toll.nonstop[i].vehicle_queue);
		toll.general_accumulator += queue_data_amount(toll.nonstop[i].vehicle_queue);
	}
}

void initial_charge(TOLL toll)
{
	cout << endl;
	cout << endl;
	cout << "----------------- CARGA INICIAL ----------------" << endl;
	cout << "NORMAL:" << endl;
	for (size_t i = 0; i < toll.max_regular; i++)
		cout << "GUICHÊ Nº" << i << ": " << queue_data_amount(toll.regular[i].vehicle_queue) << endl;
	cout << endl;
	cout << "SEM-PARAR:" << endl;
	for (size_t i = 0; i < toll.max_nonstop; i++)
		cout << "GUICHÊ Nº" << i << ": " << queue_data_amount(toll.nonstop[i].vehicle_queue) << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;
}

void processed_data(TOLL toll, double time_unity)
{
	int positionMidRegular = int(toll.max_regular / 2);
	double media = 0;
	cout << endl;
	cout << "--------------------- MÉDIAS -------------------" << endl;
	cout <<"NORMAL:"<< endl;
	for (size_t i = 0; i < toll.max_regular; i++) {
		if (i == positionMidRegular || i == positionMidRegular - 1 || i == positionMidRegular + 1) {
			media = toll.regular[i].accumulator / time_unity;
			cout << "GUICHÊ Nº" << i << " (MEIO): " << media << endl;
		}
		else {
			media = toll.regular[i].accumulator / time_unity;
			cout << "GUICHÊ Nº" << i << ": " << media << endl;
		}		
	}
	cout << endl;
	cout << "SEM-PARAR:" << endl;
	for (size_t i = 0; i < toll.max_nonstop; i++) {
		media = toll.nonstop[i].accumulator / time_unity;
		cout << "GUICHÊ Nº" << i << ": " << media << endl;
	}
	cout << endl;
	cout << "OUTROS:" << endl;
	media = toll.regular_accumulator / time_unity;
	cout << "GUICHÊS NORMAIS: " << media << endl;
	media = toll.nonstop_accumulator / time_unity;
	cout << "GUICHÊS SEM-PARAR: " << media << endl;
	media = toll.general_accumulator / time_unity;
	cout << "TODOS OS GUICHÊS: " << media << endl;
	cout << "TOTAL DE VEICULOS QUE PASSARAM PELOS GUICHES REGULARES: " << toll.regular_accumulator << endl;
	cout << "TOTAL DE VEICULOS QUE PASSARAM PELOS GUICHES NONSTOP: " << toll.nonstop_accumulator << endl;
	cout << "TOTAL DE VEICULOS QUE PASSARAM PELOS GUICHES: " << toll.regular_accumulator + toll.nonstop_accumulator << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << "---------------- CARROS RESTANTES --------------" << endl;
	cout << "NORMAL:" << endl;
	for (size_t i = 0; i < toll.max_regular; i++)
		if (i == positionMidRegular || i == positionMidRegular - 1 || i == positionMidRegular + 1)
			cout << "GUICHÊ Nº" << i << " (MEIO): " << queue_data_amount(toll.regular[i].vehicle_queue) << endl;
		else
			cout << "GUICHÊ Nº" << i << ": " << queue_data_amount(toll.regular[i].vehicle_queue) << endl;
	cout << endl;
	cout << "SEM-PARAR:" << endl;
	for (size_t i = 0; i < toll.max_nonstop; i++)
		cout << "GUICHÊ Nº" << i << ": " << queue_data_amount(toll.nonstop[i].vehicle_queue) << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;
}