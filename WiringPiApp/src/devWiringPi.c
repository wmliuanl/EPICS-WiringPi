#include <stdio.h>

#include <dbDefs.h>
#include <registryFunction.h>
#include <biRecord.h>
#include <boRecord.h>
#include <epicsExport.h>
#include <string.h>

void SetGPIO(int ChIndx, long val);
void SetMode(int ChIndx, long val);
long GetGPIO(int ChIndx);

long writeGPIO();
long readGPIO();


struct {
    long        number;
    DEVSUPFUN   report;
    DEVSUPFUN   init;
    DEVSUPFUN   init_record;
    DEVSUPFUN   get_ioint_info;
    DEVSUPFUN   write_bo;
}devWiringPibo = {
    5,
    NULL,
    NULL,
    NULL,
    NULL,
    writeGPIO,
};


struct {
    long        number;
    DEVSUPFUN   report;
    DEVSUPFUN   init;
    DEVSUPFUN   init_record;
    DEVSUPFUN   get_ioint_info;
    DEVSUPFUN   read_xxx;
    }devWiringPibi={
    5,
    NULL,
    NULL,
    NULL,
    NULL,
    readGPIO,
};



epicsExportAddress(dset,devWiringPibo);
epicsExportAddress(dset,devWiringPibi);




long writeGPIO(prec)
struct boRecord* prec;
{
    int chindx;
    prec->pact=TRUE;
    if (prec->out.type == INST_IO) {
		if(strstr(prec->out.value.instio.string,"Mode")!=NULL) {
			if(sscanf(prec->out.value.instio.string,"Mode:%d",&chindx)==1) {
				SetMode(chindx, prec->val);
			}
		}
		else {
			if(sscanf(prec->out.value.instio.string,"Ch:%d",&chindx)==1) {
				SetGPIO(chindx, prec->val);
			}
		}
    }
    prec->pact = FALSE;
    return(0);
}


long readGPIO(prec)
struct biRecord* prec;
{
    prec->pact=TRUE;
    long status;
    int chindx;
    if (prec->inp.type == INST_IO) {
		if(sscanf(prec->inp.value.instio.string,"Ch:%d",&chindx)==1) {
            status=GetGPIO(chindx);
            prec->rval= (status!=0);
        }
       else prec->rval=0;
    }
    prec->pact = FALSE;
    return(0);
}


