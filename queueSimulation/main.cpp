#include "control.h"

int main()
{
	// INSTALAÇÃO DE ADD-ONS
	setlocale(LC_ALL, "portuguese");
	// --------------------------------------------------------------

	// INICIALIZAÇÃO DE VARIAVEIS
	TIMER simulation_timer;
	TIMER arrival_timer;
	CONTROL control;
	TOLL toll;
	// --------------------------------------------------------------

	// INICIALIZAÇÃO
	if (debug) prog_data(control);
	else take_data(control);
	toll = new_toll(control.regular_tk_wdw_amount, control.nonstop_tk_wdw_amount);
	vehicle_arrival(toll, control.initial_vehicle_amount);
	initial_charge(toll);
	simulation_timer = new_timer();
	// --------------------------------------------------------------

	// LOOPING PRINCIPAL
	while (true)
	{
		if (to_continue(simulation_timer, control.simulation_time))
			break;
		if (to_continue(arrival_timer, TIME_UNITY)) {
			vehicle_arrival(toll, control.vehicle_per_time_unity);
			counter(toll);
		}
		vehicle_service(toll);
	}
	// --------------------------------------------------------------

	// EXIBE OS RESULTADOS
	processed_data(toll, control.simulation_time / TIME_UNITY);
	// --------------------------------------------------------------

	while (true);
	return EXIT_SUCCESS;
}
