X86=qemu-system-x86_64
ARM=qemu-system-arm

MEM=-m 4096
CPU=-smp cpus=2
CDROM=-cdrom image.iso
OPTS=$(MEM) $(CPU) $(CDROM)

DRIVE_1=-drive file=disk1.qcow,index=0,media=disk,format=qcow2
DRIVE_2=-drive file=disk2.raw,index=1,media=disk,format=raw

DRIVE_3=-drive file=hepiadoom.qcow2,index=0,media=disk,format=qcow2
DRIVE_4=-drive file=hepiadoom.qcow2,index=0,media=disk,format=qcow2,if=virtio

DRIVE_5=-drive file=hepiadoom-backup.qcow,index=0,media=disk,format=qcow2,if=virtio

KVM=-enable-kvm -cpu host #je suis obligé d'ajouter -cpu host sinon ca marche pas

ex1-a:
	$(X86) $(OPTS)

ex1-b:
	$(X86) $(OPTS) $(KVM)

ex1-e:
	$(X86) $(OPTS) $(DRIVE_1) $(DRIVE_2) $(KVM)

ex2-a:
	$(X86) $(MEM) $(CPU) $(KVM) -cdrom hepiadoom.ova

ex2-c:
	$(X86) $(MEM) $(CPU) $(DRIVE_3) $(KVM)

ex2-d:
	$(X86) $(MEM) $(CPU) $(DRIVE_4) $(KVM)

ex3:
	$(X86) $(MEM) $(CPU) $(DRIVE_4) $(KVM) \
	-chardev socket,path=/tmp/qga.sock,server,nowait,id=qga0 \
	-device virtio-serial \
	-device virtserialport,chardev=qga0,name=org.qemu.guest_agent.0

ex4:
	$(X86) $(MEM) $(CPU) $(DRIVE_4) $(KVM) -vga qxl

ex3-c:
	$(X86) $(MEM) $(CPU) $(DRIVE_4) $(KVM) -vga qxl \
	-device virtio-serial-pci \
	-spice port=5930,disable-ticketing \
	-device virtserialport,chardev=spicechannel10,name=com.redhat.spice.0 \
	-chardev spicevmc,id=spicechannel10,name=vdagent

tp2-ex1:
	$(X86) $(MEM) $(CPU) $(DRIVE_4) $(KVM) -vga qxl \
	-virtfs local,path=/media/thomas/Samsung_T5/Virtualisation/shared_folder,mount_tag=lol,security_model=mapped

tp2-ex2:
	$(X86) $(MEM) $(CPU) $(DRIVE_5) $(KVM) -vga qxl \
	-virtfs local,path=/media/thomas/Samsung_T5/Virtualisation/shared_folder,mount_tag=lol,security_model=mapped

tp2-ex2-b:
	$(X86) $(MEM) $(CPU) -drive file=hepiadoom-base.qcow,index=0,media=disk,format=qcow2,if=virtio $(KVM) -vga qxl \
	-virtfs local,path=/media/thomas/Samsung_T5/Virtualisation/shared_folder,mount_tag=lol,security_model=mapped

tp2-ex2-c:
	$(X86) $(MEM) $(CPU) -drive file=hepiadoom-base.qcow,index=0,media=disk,format=qcow2,if=virtio $(KVM) -vga qxl \
	-virtfs local,path=/media/thomas/Samsung_T5/Virtualisation/shared_folder,mount_tag=lol,security_model=mapped \
	-loadvm room3
