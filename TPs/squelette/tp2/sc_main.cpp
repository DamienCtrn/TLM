#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"
#include "ROM.h"

int sc_main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	/*
		MEMORY <- || <- GENERATOR
				  ||	  |
				  || -> LCDC (target)
	  	   ROM <- || <- LCDC (initiator)
	*/

	generator g("Gérard");
	Bus b("Bertrand");
	Memory m("Marco", MEM_SIZE);
	LCDC l("Leopold", sc_core::sc_time(1.0 / 25, sc_core::SC_SEC));
	ROM r("Roger");

	/* Address Mapping : (socket, addresse de début, taille) */
	b.map(m.target, MEM_ADDR_START, MEM_ADDR_SIZE);
	b.map(l.target_socket, LCDC_REG_START, LCDC_REG_SIZE);
	b.map(r.socket, ROM_MAP_START, ROM_SIZE);

	/* connect components to the bus */
	g.initiator.bind(b.target);
	b.initiator.bind(m.target);
	b.initiator.bind(r.socket);
	l.initiator_socket.bind(b.target);
	b.initiator.bind(l.target_socket);

	/* connect the interrupt port */
	l.display_int.bind(g.irq_signal);

	/* and start simulation */
	sc_core::sc_start();
	return 0;
}
