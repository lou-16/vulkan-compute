
SOURCES = main.c compute.c device.c instance.c
HEADERS = compute.h device.h instance.h
TARGET = vulkan_compute
LDFLAGS = -Wl,-rpath,/usr/local/lib -lvulkan -I/usr/local/include/

$(TARGET): $(SOURCES) ${HEADERS}
	gcc -g -O0 ${SOURCES} ${LDFLAGS} -o $(TARGET)
