#generates a new datasheet with all the data contained in scalars files (.sca)
#adds the variables iterationvars*
#after this script scalar can be processed on a experiment/repetition basics based on the values of iterationVars
rm(list=ls())
require(omnetpp)
library(multicore)
library(plyr)

setwd("Data")
files <- list.files(pattern="AlphaTest.*.sca")

minScalars <- function(file){
  scalarData <- loadDataset(file)
  iterVars <- reshape(scalarData$runattrs, idvar="runid", timevar="attrname", direction="wide")
  scalars <- merge(x=scalarData$scalars, y=iterVars, by=c("runid"))
  scalars <- scalars[scalars$name %in% values,]
  scalars <- subset(scalars, select=-c(resultkey, attrvalue.datetime, attrvalue.experiment, 
                         attrvalue.inifile,attrvalue.iterationvars, attrvalue.iterationvars2,
                         attrvalue.launchConfig, attrvalue.measurement,attrvalue.netFile,
                         attrvalue.network,attrvalue.poaFile,attrvalue.polyFile, 
                         attrvalue.processid, attrvalue.replication, attrvalue.resultdir, 
                         attrvalue.runnumber, attrvalue.seedset, attrvalue.configname, attrvalue.repetition, file))
  rm("scalarData", "iterVars")
  return(scalars)
}

#Parsear tan solo para estos vectores, para ahorrar ram
values <- c("MsgGenerated:count", "MsgReceived:count", "MsgReceived:sum",  "DataTx:sum","DataRx:sum", "AckTx:sum", "AckRx:sum")

output<-mclapply(files,FUN=minScalars, mc.preschedule= FALSE)

setwd("..")
save(list=ls(), file="./Data/minimumScalars.Rdata")
