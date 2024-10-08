## Prooxo OS is a simple OS based of davidcallanan's os-series
 Inspired by the [os-series tutorial](https://github.com/davidcallanan/os-series) by David Callanan.

## Prerequisites
- [Docker](https://www.docker.com/get-started)
- [QEMU](https://www.qemu.org/)

## Installation and Building of the Docker image
Build the image:
 - `docker build buildenv -t myos-buildenv`

Running it on windows:
To run the Docker container in the CMD you have to run: 
 - `docker run --rm -it -v "%cd%":/root/env myos-buildenv`
 
For Powershell you need to run:
 - `docker run --rm -it -v "${pwd}:/root/env" myos-buildenv`

Running it on Linux:
 - `docker run --rm -it -v "$(pwd)":/root/env myos-buildenv`

note: You have to have the Docker deamon running for both windows and linux,
for systems using systemd:
- `systemctl enable docker`
- `systemctl run docker` <br>
for windows just open the docker app and let it run in the background

## Compiling of the Kernel
To build the Kernel start the Docker container and run:
- `make build-x86_64`
## Emulate
We Develop the operating system using Qemu as our emulator
Use this command to emulate the OS:   
 - `qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso`

note: Close the emulator befor compiling again to prevent errors

You can also write the OS to an USB to run it from live Hardware (Not tested yet)

## Cleanup

Remove the build-evironment image:
 - `docker rmi myos-buildenv -f`
