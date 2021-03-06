#ifndef MEMORY_H
#define MEMORY_H

#include "ensitlm.h"

#define MEM_SIZE 0x15400
#define MEM_ADDR_START 0x2800
#define MEM_ADDR_SIZE 0x12C00
#define IMG_SIZE 76800
#define ROW_SIZE 320
#define COL_SIZE 240

SC_MODULE(Memory) {
	ensitlm::target_socket<Memory> target;

	SC_HAS_PROCESS(Memory);
	Memory(sc_core::sc_module_name name, unsigned int size);

	~Memory();

	tlm::tlm_response_status read(ensitlm::addr_t a, ensitlm::data_t & d);

	tlm::tlm_response_status write(ensitlm::addr_t a, ensitlm::data_t d);

private:
	unsigned int m_size;

public:
	/* The loader must have access to the storage */
	ensitlm::data_t *storage;
};

#endif
