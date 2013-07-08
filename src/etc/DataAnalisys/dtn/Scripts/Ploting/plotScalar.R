
rm(list= ls(all.names=TRUE))
load(file="./Data/scalarsProcessed.Rdata")
library(ggplot2)

my_theme <- theme_bw()+theme(
            axis.title = element_text(size=16),
            axis.text = element_text(size=14),
            legend.text = element_text(size=14),
            legend.title = element_blank(),
            legend.background = element_blank(),
            legend.position=c(-0.02,1.06),
            legend.justification = c(0,1))
theme_set(my_theme)
titles <-c("With ACK and Broadcast", "With ACK and Unicast", "Without ACK and Broadcast", "Without ACK and Unicast")

#Keep data only for a window size of 30

for(variable in variables){
     assign(variable, subset(get(variable)[get(variable)$window == 50 | is.na(get(variable)$window),], select=-window))
 }

pdf("Figures/RxRatio.pdf", width=7, height=4, onefile=TRUE)
i=1;
epi <- RxRatioData$dtnMethod == "Ideal"

for(ack in c(TRUE,FALSE)){
    for(broad in c(TRUE,FALSE)){
        RxRatioData$ACK[epi]<- ack
        RxRatioData$Broadcast[epi]<- broad
        AckSet <- as.logical(RxRatioData$ACK) == ack
        broadSet <- as.logical(RxRatioData$Broadcast) == broad
        print(ggplot(na.omit(RxRatioData[AckSet & broadSet,]), 
               aes(x=Nodes, y=mean, linetype=dtnMethod, colour=dtnMethod, group=dtnMethod))+
            geom_errorbar(aes(ymin=mean-ci, ymax=mean+ci), color="black", width=2.5, linetype=1, position=position_dodge(.4))+
            geom_line(size=1.3)+
            geom_point(size=2)+
            ylab("Message Delivery Ratio")+
            ylim(0.25,1))
        i<- i+1
    }
}
dev.off()


pdf("Figures/Efficiency.pdf", width=7, height=4, onefile=TRUE)
i=1;

for(ack in c(TRUE,FALSE)){
    for(broad in c(TRUE,FALSE)){
        AckSet <- as.logical(EfficiencyData$ACK) == ack
        broadSet <- as.logical(EfficiencyData$Broadcast) == broad
        print(ggplot(na.omit(EfficiencyData[AckSet & broadSet,]), 
                     aes(x=Nodes, y=mean, linetype=dtnMethod, colour=dtnMethod, group=dtnMethod))+
                  geom_errorbar(aes(ymin=mean-ci, ymax=mean+ci), color="black", width=2.5, linetype=1, position=position_dodge(.4))+
                  geom_line(size=1.3)+
                  geom_point(size=2)+
                  ylim(0,max(EfficiencyData$mean, na.rm=TRUE)*1.2)+
                  theme(legend.position=c(1,1),
                        legend.justification = c(1,1))+
                  ylab("Total Tx Bytes/Delivered Bytes"))
        i<- i+1
    }
}
dev.off()

pdf("Figures/TotalLosses.pdf", width=7, height=4, onefile=TRUE)
i=1;

for(ack in c(TRUE,FALSE)){
    for(broad in c(TRUE,FALSE)){
        AckSet <- as.logical(LossRatioData$ACK) == ack
        broadSet <- as.logical(LossRatioData$Broadcast) == broad
        print(ggplot(na.omit(LossRatioData[AckSet & broadSet, ]), aes(x=Nodes, y=mean, fill=dtnMethod))+
                  ylim(0,max(LossRatioData$mean, na.rm=TRUE)*1.15)+
                  geom_bar(position="dodge", stat="identity", colour="black")+
                  geom_errorbar(aes(ymin=mean-ci, ymax=mean+ci), color="black", width=2.5, linetype=1, position=position_dodge(9))+
                  geom_text(aes(label=round(mean,3)), vjust=-2, position=position_dodge(9), size=3)+
                  ylab("One-Hop Packet Loss Ratio"))
        i<-i+1
    }
}
dev.off()


pdf("Figures/TotalData.pdf", width=7, height=4, onefile=TRUE)
i=1;

for(ack in c(TRUE,FALSE)){
    for(broad in c(TRUE,FALSE)){
        AckSet <- as.logical(TotalByteTxData$ACK) == ack
        broadSet <- as.logical(TotalByteTxData$Broadcast) == broad
        print(ggplot(na.omit(TotalByteTxData[AckSet & broadSet, ]), aes(x=Nodes, y=mean/Nodes/1e6, fill=dtnMethod)) +
                  geom_bar(position="dodge", stat="identity", colour="black")+
                  geom_errorbar(aes(ymin=mean/Nodes/1e6-ci/Nodes/1e6, ymax=mean/Nodes/1e6+ci/Nodes/1e6), color="black", width=2.5, linetype=1, position=position_dodge(9))+
                  geom_text(aes(label=paste(round(mean/Nodes/1e6,2),"MB",sep="")), vjust=1.5, position=position_dodge(9), size=2)+
                  ylim(0,max(TotalByteTxData$mean/TotalByteTxData$Nodes/1e6,na.rm=TRUE)*1.2)+
                  ylab("Tx Bytes per Node (MB)"))
        i<-i+1
    }
}

dev.off()

pdf("Figures/SendToChannelData.pdf", width=7, height=4, onefile=TRUE)
i=1;

for(ack in c(TRUE,FALSE)){
  for(broad in c(TRUE,FALSE)){
    AckSet <- as.logical(SentToChannelData$ACK) == ack
    broadSet <- as.logical(SentToChannelData$Broadcast) == broad
    print(ggplot(na.omit(SentToChannelData[AckSet & broadSet, ]), aes(x=Nodes, y=mean/Nodes/1e6, fill=dtnMethod)) +
            geom_bar(position="dodge", stat="identity", colour="black")+
            geom_errorbar(aes(ymin=mean/Nodes/1e6-ci/Nodes/1e6, ymax=mean/Nodes/1e6+ci/Nodes/1e6), color="black", width=2.5, linetype=1, position=position_dodge(9))+
            geom_text(aes(label=paste(round(mean/Nodes/1e6,2),"MB",sep="")), vjust=1.5, position=position_dodge(9), size=2)+
            ylim(0,max(SentToChannelData$mean/SentToChannelData$Nodes/1e6,na.rm=TRUE)*1.2)+
            ylab("Tx Bytes per Node (MB)"))
    i<-i+1
  }
}

dev.off()


pdf("Figures/CollisionsData.pdf", width=7, height=4, onefile=TRUE)
i=1;

for(ack in c(TRUE,FALSE)){
  for(broad in c(TRUE,FALSE)){
    AckSet <- as.logical(ColNodeData$ACK) == ack
    broadSet <- as.logical(ColNodeData$Broadcast) == broad
    print(ggplot(na.omit(ColNodeData[AckSet & broadSet, ]), aes(x=Nodes, y=mean, fill=dtnMethod))+
            ylim(0,max(ColNodeData$mean, na.rm=TRUE)*1.15)+
            geom_bar(position="dodge", stat="identity", colour="black")+
            geom_errorbar(aes(ymin=mean-ci, ymax=mean+ci), color="black", width=2.5, linetype=1, position=position_dodge(9))+
            geom_text(aes(label=round(mean,3)), vjust=-2, position=position_dodge(9), size=3)+
            ylab("Collisions sensed per node"))
    i<-i+1
  }
}
dev.off()
