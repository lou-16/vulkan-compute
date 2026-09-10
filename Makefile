
SOURCES = main.c log.c compute.c device.c instance.c pipeline.c
HEADERS = compute.h device.h instance.h pipeline.h
TARGET = vulkan_compute
LDFLAGS = -Wl,-rpath,/usr/local/lib -lvulkan -I/usr/local/include/

SHADER_SRC = shader.comp 
SHADER_BIN = comp.spv

$(TARGET): $(SOURCES) ${HEADERS} ${SHADER_BIN}
	gcc -g -O0 -fsanitize=address -fno-omit-frame-pointer ${SOURCES} ${LDFLAGS} -o $(TARGET)

${SHADER_BIN} : ${SHADER_SRC}
	glslangValidator -V ${SHADER_SRC} -o ${SHADER_BIN}
