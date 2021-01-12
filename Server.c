#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<ctype.h>
#include "encryptdecr.h"

void error(const char *err){
	perror(err);
	exit(1);
}

int ser_main(int argc,char *argv[])
{
      if(argc<2){
    	fprintf(stderr,"Not enough Agruments!!");    
    	exit(1);
       }
       
       int portno,len;
       char buffer[1024];  //to store strings
       FILE *fp_server=NULL;
       struct sockaddr_in server_addr,client_addr;
       socklen_t clientlen;
       
       //creating socket
       int sockfd=socket(AF_INET,SOCK_STREAM,0);
       if(sockfd<0)
	       error("Error creating socket!!");
       
       bzero((char *)&server_addr,sizeof(server_addr));
       
       portno=atoi(argv[1]);
       
       int i;
       server_addr.sin_family=AF_INET;
       server_addr.sin_addr.s_addr=INADDR_ANY;;
       server_addr.sin_port=htons(portno);
       
       if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0 )
       	error("Attention:Socket Binding Failed!!");
       
       listen(sockfd,5);
       
       clientlen=sizeof(client_addr);
       
       int newsockfd;
       printf("Server Available for requests .......\n");
              
      /* printf("\n\n>>>ENTER THE FIRST PRIME NUMBER: ");
			scanf("%ld",&p);
		 	//checking for prime numbers
			flag=prime(p);
			if(flag==0) {
				printf("\nWRONG INPUT:\nAttention:Prime Number Required!!\n");
				exit(1);
			}
			
			printf("\n>>>ENTER THE ANOTHER PRIME NUMBER:");
			scanf("%ld",&q);
			flag=prime(q);
			if(flag==0||p==q) {
				printf("\nWRONG INPUT:\nAttention:Prime Number Required!!\n");
				exit(1);
		 }	*/ 
			p=53l;
			q=59l;
	n=p*q;
	t=(p-1)*(q-1);        //totient
	ce();             //public key(n,e)
	d=cd(); 
    //Preserving values
      n1=n;
      e1=e;
     long int nc,ec;
       newsockfd=accept(sockfd,(struct sockaddr *)&client_addr,&clientlen);
       
	if(newsockfd<0)
	      	error("Attention: Error on Accepting request");
       printf("Connection Established with the client!!!!!:%d\n",ntohs(client_addr.sin_port));

      
       printf("\nTaking the public key to perform encryption\n");
       
       //****************Public Key=(n,e)***********************
       // printf("%ld,%ld,%ld",n,e,d);
      //printf("\n%ld,%ld,%ld\n",n1,e1,d);
      
      bzero(buffer,256);
       len=read(newsockfd,buffer,255);
       if(len<0)
        	error("Error Reading from client!!");
       n=atoi(buffer);
		       
       bzero(buffer,256);
       sprintf(buffer,"%ld",n1);

       len=write(newsockfd,buffer,256);
       if(len<0)
        	error("Error writing to client!!");
        	
	bzero(buffer,256);
       len=read(newsockfd,buffer,255);
       if(len<0)
       	error("Error Reading from client!!");
       e=atoi(buffer);
       
       bzero(buffer,256);
	sprintf(buffer,"%ld",e1);
        write(newsockfd,buffer,2);

       printf("CLIENT: *****PUBLIC KEY:(%ld,%ld)*****\n",n,e);
      //printf("%s",buffer);
         bzero(buffer,256);
         nc=n;
         ec=e;
         fp_server=fopen("ServerFile.txt","w");
         
       while(1){ 
        	fputs("Client: ",fp_server);
        	bzero(buffer,1024);
		len=read(newsockfd,en,1024); 
		i=0;
		while(en[i]!=-1){
			putc(en[i],fp_server);
			i++;
		}
		//fputs(en,fp_server);
		fprintf(fp_server,"\n");
		i=0;
		//printf("\n>>>CLIENT:");
		//printf("\n     ^^^^^^  Original Message(Actual Message Recieved): ");
		//while(en[i]!=-1)
		//	printf("%c",en[i++]);
		//printf("  ^^^^^^\n");
		
		//Decrypting the message recieved
		n=n1;
		e=e1;
		
		decrypt();   //Actual Message stored in msg array
		          	
		if(len<0)
			error("Error Reading from client!!");
			
		bzero(en,1024);
		strncpy(buffer,msg,1024);
		bzero(msg,1024);

		//printf("     Decrypted Message: %s\n",buffer);
		printf(">>>CLIENT: %s\n",buffer);
		//printf("\t--------------------------------------------------------------------------");
		
		i=strncmp("bye",buffer,3);
		//printf("%d ",strlen(buffer));
		if(i==0){
			//write(newsockfd,"Bye bye have a nice day",strlen("Bye bye have a neice day"));
			fputs("Server:",fp_server);
			strncpy(enc,"bye bye have a nice day",1024);
			n=nc;
			e=ec;
			
			encrypt();
			//for(i=0;en[i]!=-1;i++);
			i=0;
			fputs("Server:",fp_server);
			while(en[i]!=-1){
				putc(en[i],fp_server);
				i++;
			}
			
			fprintf(fp_server,"\n");
			len=write(newsockfd,en,(i+1)*8);  
			printf("\n Client %d Disconnected \n",ntohs(client_addr.sin_port));
			break;
		}
		
		bzero(buffer,1024);
		printf(">>> ");                      

		fgets(buffer,1024,stdin);
		strncpy(enc,buffer,1024);		      
	

		n=nc;
		e=ec;
		encrypt();
		//bzero(buffer,1024);

		//Encrypted Message
	        //printf("\n\t--------------------------------------------------------------------------");
		//printf("\n     ^^^^^^The Encrypted Message is: ");
		for(i=0;en[i]!=-1;i++){
		//	printf("%c",en[i]);
		//	buffer[i]=en[i];
		}
		//printf("^^^^^^\n");
		//printf("\t--------------------------------------------------------------------------");
		
		//i=i+1;
		len=write(newsockfd,en,(i+1)*8);              //writing whole array en to client
		fputs("Server:",fp_server);
		i=0;
		while(en[i]!=-1){
			putc(en[i],fp_server);
			i++;
		}
		//fputs(en,fp_server);
		fprintf(fp_server,"\n");

		if(len<0)
			error("Error Writing to client!!");

				     
		i=strncmp("bye",buffer,3);
		//printf("%d ",strlen(buffer));
		//bzero(en,sizeof(en));
		bzero(buffer,1024);

		if(i==0)
			break;
		}
		fclose(fp_server);
		close(newsockfd);
		close(sockfd);
		return 0;
}
