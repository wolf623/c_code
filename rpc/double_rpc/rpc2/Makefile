
# This is a template Makefile generated by rpcgen

# Parameters

SERVER = rpc2

SOURCES_CLNT.c = 
SOURCES_CLNT.h = 
SOURCES_SVC.c = 
SOURCES_SVC.h = 
SOURCES.x = rpc2.x

TARGETS_SVC.c = rpc2.c mytime.c rpc1_svc.c rpc1_server.c rpc1_xdr.c rpc2_clnt.c rpc2_client.c rpc2_xdr.c 

OBJECTS_SVC = $(SOURCES_SVC.c:%.c=%.o) $(TARGETS_SVC.c:%.c=%.o)
# Compiler flags 

CFLAGS += -g -lpthread
LDLIBS += -lnsl
RPCGENFLAGS = 

# Targets 

all : $(SERVER)

$(OBJECTS_SVC) : $(SOURCES_SVC.c) $(SOURCES_SVC.h) $(TARGETS_SVC.c) 

$(SERVER) : $(OBJECTS_SVC) 
	$(LINK.c) -o $(SERVER) $(OBJECTS_SVC) $(LDLIBS)

 clean:
	 $(RM) core $(TARGETS) $(OBJECTS_CLNT) $(OBJECTS_SVC) $(SERVER)

