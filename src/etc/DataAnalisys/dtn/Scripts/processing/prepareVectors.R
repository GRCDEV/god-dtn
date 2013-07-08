#This script load every vector from our simulation and generates a histogram for every runid which contains the
#number of messages that experienced a delay smaller than the bin value. It is a kind of ecdf where the maximum
#value is the number of sent messages NOT the number of received messages.

#This must be run after running processScalars.R
require(omnetpp)
library(plyr)

rm(list= ls(all.names=TRUE))
load(file="./Data/scalarsProcessed.Rdata")
vectorData<-loadDataset(c("./Data/AckTest/*.vec","./Data/WindowTest/*.vec", "./Data/Epidemic/*.vec")) #load all the collected data
densityResults <- runidResult[1:7]
epiResult <- densityResults[runidResult$dtnMethod == "Ideal",]

densityResults <- na.omit(densityResults[densityResults$window ==30 & densityResults$broadcast == FALSE,])
densityResults <- rbind.fill(densityResults, epiResult)

bins<-seq(15,1000,15)
densities <- matrix(NA, length(densityResults$runid), length(bins))
means<-list()
iter <- 1
for(runid in densityResults$runid){
    resultKey <- vectorData$vectors$resultkey[vectorData$vectors$runid == runid & 
                                              (vectorData$vectors$name == "MsgReceivedDelay:vector" ) ]
    vectors <- loadVectors(vectorData, resultKey)
    resultKey <- vectors$vectors$resultkey[vectors$vectors$name == "MsgReceivedDelay:vector"]
    totalNumber <- runidResult$TxMsg[runidResult$runid == runid]
    delayVector <- vectors$vectordata$y[vectors$vectordata$resultkey == resultKey]
    means<-c(means,mean(delayVector))
    density <- lapply(bins,
           FUN=function(n){
                    sum(delayVector < n)
                })
    density <- as.numeric(density)/totalNumber
    densities[iter, ] <- density
    iter<- iter+1
    closeAllConnections()
}
densities.df<- data.frame(runid=densityResults$runid, as.data.frame(densities))
densityResults$delay<-as.numeric(means)
#rm(means,densities, density, delayVector, iter, resultKey, runid, totalNumber)
densityResults <- merge(densityResults, densities.df)

#rm(densities.df,means.df)

meanDelay<-summarySE(densityResults, measurevar="delay", groupvars=c("dtnMethod","Nodes"))

densityResults <- subset(densityResults, select=-c(runid, repetition,ACK, broadcast, window))
colnames(densityResults)[4:69] <- bins
byList=list(dtnMethod = densityResults$dtnMethod, Nodes = densityResults$Nodes)
    
densityMeans <- aggregate(subset(densityResults,select=-c(dtnMethod, Nodes)),
                   byList, 
                   FUN=mean)
densityConf <- aggregate(subset(densityResults,select=-c(dtnMethod, Nodes)),
                          byList,
                          FUN=function(dat){tTest<-t.test(x=dat)
                                            tTest$estimate-tTest$conf.int[1]})


save(list=c("meanDelay", "densityMeans", "densityConf"), file="./Data/vectorsProcessed.Rdata")
