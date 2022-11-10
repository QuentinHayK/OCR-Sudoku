CC = gcc                                                                        
CPPFLAGS =                                                                      
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`                
LDFLAGS =                                                                      
LDLIBS = `pkg-config --libs sdl2 SDL2_image`                                    
                                                                        
all: preprocessing                                                          
                                                                        
SRC = preprocessing.c                                                    
OBJ = ${SRC:.c=.o}                                                              
EXE = ${SRC:.c=}                                                                
                                                                        
                                           
preprocessing: preprocessing.o                                                          
                                                                        
.PHONY: clean                                                                  
                                                                        
clean:                                                                          
 ${RM} ${OBJ}                                                            
 ${RM} ${EXE}                                                            
                            