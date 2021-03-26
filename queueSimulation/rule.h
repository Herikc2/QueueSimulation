#pragma once

#include <iostream>
#include "timer.h"
#include "toll.h"

enum { REGULAR, NONSTOP };
enum { TU_1, TU_2 };
enum { TU_5, TU_10, TU_8 };

void insertion_divider(int number_vehicles[], int vehicle_per_time_unity)
{
	number_vehicles[NONSTOP] = int(0.3 * vehicle_per_time_unity); // Veiculos sem parar
	number_vehicles[REGULAR] = int(0.7 * vehicle_per_time_unity); // Veiculos regulares
	int vehicles = number_vehicles[REGULAR] + number_vehicles[NONSTOP];

	if (vehicles < vehicle_per_time_unity) {
		int vehicles_compensator = vehicle_per_time_unity - vehicles;

		for (size_t i = 0; i < vehicles_compensator; i++) {
				number_vehicles[NONSTOP]++;
		}
	}
}

void nonstop_divider(int nonstop[], int nonstop_amount)
{
	nonstop[TU_1] = int(0.9 * nonstop_amount);
	nonstop[TU_2] = int(0.1 * nonstop_amount);
	int vehicles = nonstop[TU_1] + nonstop[TU_2];

	if (vehicles < nonstop_amount) {
		int vehicles_compensator = nonstop_amount - vehicles;

		for (size_t i = 0; i < vehicles_compensator; i++) {
				nonstop[TU_1]++;
		}
	}
}

void regular_divider(int regular[], int regular_amount)
{
	regular[TU_5] = int(0.2 * regular_amount);
	regular[TU_10] = int(0.3 * regular_amount);
	regular[TU_8] = int(0.5 * regular_amount);
	int vehicles = regular[TU_5] + regular[TU_10] + regular[TU_8];

	if (vehicles < regular_amount) {
		int vehicles_compensator = regular_amount - vehicles;

		for (size_t i = 0; i < vehicles_compensator; i++) {
			regular[TU_5]++;
		}
	}
}

size_t smaller_queue(TICKET_WINDOW ticket_window[], int size)
{
	size_t index = 0;
	int smaller = queue_data_amount(ticket_window[index].vehicle_queue);
	for (size_t i = 1; i < size; i++)
		if (queue_data_amount(ticket_window[i].vehicle_queue) < smaller) {
			smaller = queue_data_amount(ticket_window[i].vehicle_queue);
			index = i;
		}
	return index;
}

// cria os veiculos
void create_vehicles(VEHICLE vehicles[], int vehicle_amount)
{
	int vehicle_percent[2];
	int vehicle_nonstop[2];
	int vehicle_regular[3];
	
	// divide os veiculos pela porcentagem
	insertion_divider(vehicle_percent, vehicle_amount);
	nonstop_divider(vehicle_nonstop, vehicle_percent[NONSTOP]);
	regular_divider(vehicle_regular, vehicle_percent[REGULAR]);

	// cria os veiculos cada um com sua regra especifica
	int c_vp = 0, c_vn = 0, c_vr = 0;
	for (int i = 0; i < vehicle_amount; i++) {
		if (c_vp < vehicle_percent[NONSTOP]) {
			if (c_vn < vehicle_nonstop[TU_1]) {
				vehicles[i] = new_vehicle(1 * TIME_UNITY, NONSTOP);
				c_vn++;
			}
			else {
				vehicles[i] = new_vehicle(2 * TIME_UNITY, NONSTOP);
			}
			c_vp++;
		}
		else {
			if (c_vr < vehicle_regular[TU_5]) {
				vehicles[i] = new_vehicle(5 * TIME_UNITY, REGULAR);
				c_vr++;
			}
			else if (c_vr < vehicle_regular[TU_5] + vehicle_regular[TU_10]) {
				vehicles[i] = new_vehicle(10 * TIME_UNITY, REGULAR);
				c_vr++;
			}
			else {
				vehicles[i] = new_vehicle(8 * TIME_UNITY, REGULAR);
			}
		}
	}
}

void insert_vehicles(TOLL& toll, VEHICLE vehicles[], int vehicle_amount)
{
	// insere os veiculos
	int amountMid[3];
	int meioRegular = int(toll.max_regular / 2);
	double current;
	bool availableMid[3];	
	for (int i = 0; i < 3; i++)
		availableMid[i] = true;

	for (size_t i = 0; i < vehicle_amount; i++) {
		if (vehicles[i].toll == NONSTOP) {
			size_t index = smaller_queue(toll.nonstop, toll.max_nonstop);
			queue(toll.nonstop[index].vehicle_queue, vehicles[i]);
		}
		else if (vehicles[i].toll == REGULAR) {
			for (int j = 0; j < toll.max_regular; j++) {
				current = queue_data_amount(toll.regular[j].vehicle_queue) * 1.3;
				amountMid[0] = queue_data_amount(toll.regular[meioRegular - 1].vehicle_queue);
				amountMid[1] = queue_data_amount(toll.regular[meioRegular].vehicle_queue);
				amountMid[2] = queue_data_amount(toll.regular[meioRegular + 1].vehicle_queue);
				if (amountMid[0] > current)
					availableMid[0] = false;
				if (amountMid[1] > current)
					availableMid[1] = false;
				if (amountMid[2] > current)
					availableMid[2] = false;
				if (!availableMid[0] && !availableMid[1] && !availableMid[2])
					break;
			}

			if (availableMid[0]) {
				queue(toll.regular[meioRegular - 1].vehicle_queue, vehicles[i]);
			}
			else if (availableMid[1]) {
				queue(toll.regular[meioRegular].vehicle_queue, vehicles[i]);
			}
			else if (availableMid[2]) {
				queue(toll.regular[meioRegular + 1].vehicle_queue, vehicles[i]);
			}
			else {
				size_t index = smaller_queue(toll.regular, toll.max_regular);
				queue(toll.regular[index].vehicle_queue, vehicles[i]);
			}
			for (int i = 0; i < 3; i++)
				availableMid[i] = true;
		}
	}
}

void vehicle_arrival(TOLL& toll, int vehicle_amount)
{
	VEHICLE* vehicles = new VEHICLE[vehicle_amount];

	create_vehicles(vehicles, vehicle_amount);
	insert_vehicles(toll, vehicles, vehicle_amount);

	delete[] vehicles;
}

// Atendimento dos guichês.
void vehicle_service(TOLL& toll)
{
	for (size_t i = 0; i < (unsigned)toll.max_nonstop; i++)
		if (toll.nonstop[i].vehicle_queue.first != NULL)
			if (to_continue(toll.nonstop[i].vehicle_queue.first->data.timer, toll.nonstop[i].vehicle_queue.first->data.time))
				dequeue(toll.nonstop[i].vehicle_queue);
	for (size_t i = 0; i < (unsigned)toll.max_regular; i++)
		if (toll.regular[i].vehicle_queue.first != NULL)
			if (to_continue(toll.regular[i].vehicle_queue.first->data.timer, toll.regular[i].vehicle_queue.first->data.time))
				dequeue(toll.regular[i].vehicle_queue);
}