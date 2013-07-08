#In this script we will create a datasheet from collecting data per every simulation
#Our data is in minimumScalars
rm(list=ls(all.names=TRUE))
library(plyr)
library(multicore)

load(file="./Data/minimumScalars.Rdata")
groupvars <- c("runid", "dtnMethod", "repetition", "Nodes", "ACK", "broadcast", "window")

data<-mclapply(output, parse, mc.preschedule=FALSE)
runidResult<-rbind.fill(rev(data))
names(runidResult)[1:6]<-c("runid","dtnMethod", "Nodes", "ACK", "Broadcast", "window")
runidResult$ACK <- as.logical(as.character(runidResult$ACK))
runidResult$Broadcast <- as.logical(as.character(runidResult$Broadcast))
runidResult$Nodes <- as.numeric(as.character(runidResult$Nodes))
runidResult$dtnMethod <- factor(runidResult$dtnMethod)
levels(runidResult$dtnMethod) <- c("Greedy", "GeOpps", "Msdp", "Ideal")

runidResult <- runidResult[order(runidResult$Nodes, runidResult$ACK, runidResult$Broadcast, runidResult$dtnMethod, na.last=TRUE),]
runidResult$RxRatio <- runidResult$RxMsg/runidResult$TxMsg
runidResult$TotalByteTx <- runidResult$TotalDataTx+runidResult$TotalAckTx
runidResult$TotalByteRx <- runidResult$TotalDataRx+runidResult$TotalAckRx
runidResult$Efficiency <- runidResult$ReceivedBytes / runidResult$SentToChannel
runidResult$ColNode   <- runidResult$Collisions / as.numeric(runidResult$Nodes)
runidResult$LossRatio <- (runidResult$TotalDataTx-runidResult$TotalDataRx)/runidResult$TotalDataTx
runidResult$SentNode <- runidResult$SentToChannel / as.numeric(runidResult$Nodes)

groupvars=names(runidResult)[c(2:6)]
variables <- c()
for(value in names(runidResult)[-c(1:8)]){
    assign(paste(value,"Data", sep=""),summarySE(runidResult, measurevar=value, groupvars=groupvars))
    variables <- c(variables, paste(value,"Data", sep=""))
}

rm(minimumScalars, data, files, output)
save(list=ls(), file="./Data/scalarsProcessed.Rdata")

