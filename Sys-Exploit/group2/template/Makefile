SHELL := /bin/bash
DISK=disk.raw
DISK_SIZE=256K

help:
	@echo "Available targets:"
	@echo "  test_all       : builds and run all tests"
	@echo "  test_vga_emul  : builds and run the display tests on a guest VM featuring VGA emulation"
	@echo "  test_vga_pv    : builds and run the display tests on a guest VM featuring VGA paravirtualization"
	@echo "  test_disk_emul : builds and run regression tests on a guest VM featuring disk emulation"
	@echo "  test_disk_pv   : builds and run regression tests on a guest VM featuring disk paravirtualization"
	@echo "  clean          : deletes all generated files (not the disk though)"

test_all: test_vga_emul test_vga_pv test_disk_emul test_disk_pv

test_vga_emul: guest vmm $(DISK)
	$(MAKE) -C $< $@.bin
	vmm/vmm -guest guest/$@.bin -disk $(DISK)

test_vga_pv: guest vmm $(DISK)
	$(MAKE) -C $< $@.bin
	vmm/vmm -guest guest/$@.bin -disk $(DISK)

test_disk_emul: guest vmm $(DISK)
	$(MAKE) -C $< $@.bin
	vmm/vmm -guest guest/$@.bin -disk $(DISK)
	@echo "Tests passed?"
	diff $(DISK) tests/disk_ref.raw
	@echo "Tests passed :-)"

test_disk_pv: guest vmm $(DISK)
	$(MAKE) -C $< $@.bin
	vmm/vmm -guest guest/$@.bin -disk $(DISK)
	@echo "Tests passed?"
	diff $(DISK) tests/disk_ref.raw
	@echo "Tests passed :-)"

benchmark_disk_emul: guest vmm $(DISK)
	$(MAKE) -C $< $@.bin
	time vmm/vmm -guest guest/$@.bin -disk $(DISK)

benchmark_disk_pv: guest vmm $(DISK)
	$(MAKE) -C $< $@.bin
	time vmm/vmm -guest guest/$@.bin -disk $(DISK)
	
vmm:
	$(MAKE) -C $@

$(DISK):
	qemu-img create -f raw $(DISK) $(DISK_SIZE)

clean:
	$(MAKE) -C vmm $@
	$(MAKE) -C guest $@

.PHONY: vmm $(DISK) clean