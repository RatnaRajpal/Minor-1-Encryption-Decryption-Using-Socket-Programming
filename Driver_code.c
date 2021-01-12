#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
//#include "EncryptionDec.h"
#include "Server.c"
#define MAX_TREE_HEIGHT 100

char data[26],*chr,*codes[128]={0};
char abcdef[1000]="";
int freq[26];
char buf[1024];                  //store characters and codes
//char enc[1024];//encoding
//void str_cat(char* str, char* parentcode, char add);

int codelen(char* code) 
{ 
    int l = 0; 
    while (*(code + l) != '\0') 
        l++; 
    return l; 
} 
int fib(int n) 
{ 
    if (n <= 1) 
        return n; 
    return fib(n - 1) + fib(n - 2); 
} 
void str_cat(char* str, char* parentcode, char add) 
{ 
    int i = 0; 
    while (*(parentcode + i) != '\0')  
    { 
        *(str + i) = *(parentcode + i); 
        i++; 
    } 
    if (add != '2')  
    { 
        str[i] = add; 
        str[i + 1] = '\0'; 
    } 
    else
        str[i] = '\0'; 
}
struct Node_Heap{
char data;                             //stores individual characters
int freq;                         //stores number of occurences of the character
struct Node_Heap *left,*right;         //structure of structure as we do not know the exact number of nodes How many left and right childs will be there
};                               // now the given structure can be called as node

/* -----------------------------
  |Left   | data  |freq  |right |    ------>Node_Heap  OR Node
  |       |       |      |      |
   ----------------------------- */
   
 struct Heap{ 
   int size;
   int capacity;                   //capacity =total amontof val size = no of nodes occupied
   struct Node_Heap** array;                 //array of node pointers
   }*mheap;
  
  
 
 void createHeap(int capacity){
 //root=(struct Node_Heap*)malloc(sizeof(struct Node_Heap));
     mheap=(struct Heap*)malloc(sizeof(struct Heap));
     mheap->size=0;                    //initially all nodes empty
     mheap->capacity=capacity;        //a heap array can have max of elements
     mheap->array=(struct Node_Heap**)malloc(mheap->capacity * sizeof(struct Node_Heap*));
     }
     
 /*
	 heap created!!
	 Size=NULL
	 Capacity=capacity
	 array=memory allocated with null values
 */
  

 //adding newNode to Heap
 struct Node_Heap* newNode(char data,int freq){
	 struct Node_Heap* temp=(struct Node_Heap*)malloc(sizeof(struct Node_Heap));
	 temp->left=NULL;  //initially we are creating the leaf nodes
	 temp->right=NULL;
	 temp->data=data;
	 temp->freq=freq;
	 return temp;
 }
 
 //swapping of nodes during Heapifying
 void swapping_nodes(struct Node_Heap** a,struct Node_Heap** b){
	 struct Node_Heap* temp=*a;
	 *a=*b;
	 *b=temp;
 }
 
 void Heapify(int index){
	int small_index=index,left=2*index+1,right=2*index+2;          //left child lies at pos 2*i+1 right at 2*l+2
	if(left<mheap->size && mheap->array[left]->freq<mheap->array[small_index]->freq)
	small_index=left;

	if(right<mheap->size && mheap->array[right]->freq<mheap->array[small_index]->freq)
	small_index=right;

	if(small_index!=index){
	swapping_nodes(&mheap->array[small_index],&mheap->array[index]);
	Heapify(small_index);
	}

}

//to extract minimum value from the node
struct Node_Heap* minNode(){
	struct Node_Heap* temp =mheap->array[0];
	mheap->array[0]=mheap->array[--mheap->size];
	Heapify(0);
	return (temp);
}

//inserting node at appropriate position in Heap to build hoffman tree
void insert_Node(struct Node_Heap* node){
	mheap->size++;
	int i=mheap->size-1;
	while(i!=0 && node->freq < mheap->array[(i-1)/2]->freq){
		mheap->array[i]=mheap->array[(i-1)/2];
		i=(i-1)/2;
	}
	mheap->array[i]=node;
     }
     
void build_Heap(){
	int n=mheap->size-1,i;
	for(i=(n-1)/2;i>=0;i--)
		Heapify(i);
	}
	
void create_build(char data[],int freq[],int capacity){
	createHeap(capacity);                       //Empty array
	int i=0;
	//inserting data and frequency values in the Heap array
	for(i=0;i<capacity;i++)                          
		mheap->array[i]=newNode(data[i],freq[i]);
		/*mheap->array[i]->data=data[i];
		mheap->array[i]->freq=freq[i];
		mheap->array[i]->left=NULL;
		mheap->array[i]->right=NULL;
		Basically only adding a new node*/
	mheap->size=capacity; //every node is a leaf node
 	
 	build_Heap();                //performing sorting an building Heap
 	
 	}
 	
 struct Node_Heap* buildHuffmanTree(char data[],int freq[],int capacity){
	 struct Node_Heap *left,*right,*top;
	 
	  create_build(data,freq,capacity);                     //array are passed as pointers to functions only the base address is passes
	  
	  //Iterate while the size is not equal to 1
	  
	  while(mheap->size!=1){
	  left=minNode();
	  right=minNode();
	  
	  top=newNode('$',left->freq+right->freq);
	  /*top->data='$';
	  top->freq=left_c->freq+right_c->freq;*/
	  
	  /*        ---------
		   |   top   |                                       ---------->data='$' ;freq=left_c->freq+right_c->freq;
		    ---------
		    /     \
		   / 	   \
		  / 	    \
	      --------    --------
	     | left_c |  | right_c|
	      --------    --------
	      
	  */
	  
	  top->left=left;
	  top->right=right;
	  
	  insert_Node(top);                    //internal node
	  }
	  //the left over node is the root node
	  return minNode();
	  }
	
int isLeaf(struct Node_Heap* root){
	return (!root->right && !root->left);
	}
	

/*void printArr(char arr[],int n,char data){

	int i;
	
	for(i=0;i<n;i++){
	printf("%c",arr[i]);
	
	}
	
       codes[data]=arr;
       printf("\n%s",codes[data]);
       printf("\n");

}*/

	
void encode(char *var){

	while(*chr){
		//printf("Encoding");
		//printf("%c \n %ld\n",*arr,strlen(arr));
		strcpy(var,codes[*chr]);
		var +=strlen(codes[*chr++]);
	}
}
void printCodes(struct Node_Heap* root,char arr[],int top){
	//assign 0 to left tree
	static char *out=buf;
	if(root->left){
		arr[top]='0';
		printCodes(root->left,arr,top+1);
	}
	
	//assign 1 to the right edge
	if(root->right){
		arr[top]='1';
		printCodes(root->right,arr,top+1);
	}
	
	//check for leaf node;
	//if leaf node it has one of the input characters
	//print the character and its code from arr[]
	if(isLeaf(root)){
	        arr[top]=0;
	        strcpy(out,arr);
	        codes[root->data]=out;
	        out +=top+1;
		/*printf("%c: ",root->data);
		printArr(arr,top,root->data);*/
		}
	
	}
	
void decode(char* str,char *ans,struct Node_Heap* root){
	
	struct Node_Heap *curr=root;
	while(*str){
	//printf("%d",curr->freq);
	if(*str++ == '0'){
	 	curr=curr->left;             //traverse left
	 	//printf("%s\n",ans);
	 }
	else{ 
		//printf("%dIn else\n",curr->freq);
		curr=curr->right;
		
	}

	if(isLeaf(curr)){
		strncat(ans,&curr->data,1);
		curr=root;
	} 

}
	putchar('\0');	
}

	
struct Node_Heap* HuffmanCode(char data[],int freq[],int capacity){
	
	struct Node_Heap* root=buildHuffmanTree(data,freq,capacity);  //at the end we will have only one root node hence one node is considered
	//printf("%d",root->freq);
	//printing Huffman Codes from the tree
	
	char arr[100];
	int top=0;
	
	printCodes(root,arr,top);
	//printf("%d",root->freq);
	return root;
}

int search(char arr[],char key,int size){
	int i=0;
	for(i=0;i<size;i++){
	if(arr[i]==key)
		return i;
	}
	return -1;
	}
void print_codes(){
	int i;
	for(i=0;i<128;i++)
		if(codes[i]) printf("-> < %c: %s >\n",i,codes[i]);
		}

int frequency_size(char arr[]){
	int i=0,j=0,idx=0;
	while(arr[i]!='\0'){
	arr[i]=tolower(arr[i]);
		idx=search(data,arr[i],j);
		if(idx!=-1)
			freq[idx]++;
		else{
		data[j]=arr[i];
		freq[j]=1;
		j++;
		}
	i++;	
	}
	return j;
}

	
int main(int argc,char *argv[]){
	int ch;
	int pno;
	char arr[1024];
	int i=0,j=0;
	printf("\n -----------------------------------------------------------------------------------------------------------------------");
	printf("\n|\t\t**************WELCOME TO THE FAST AND SECURE DATA TRANSMISSION CHANNEL*******************\t\t|");
	printf("\n -----------------------------------------------------------------------------------------------------------------------");
	
	printf("\n\t\tDATA SECURING:\
	\n\t\t\t1. Simple Text Encryption Decryption Along With Encoding Decoding.\
	\n\t\t\t2. Image Encryption Deryption\n\
	\tDATA TRANSMISSION:\n\t\t\t3. Chat Encryption\n\
	\t\t4. Help\n\
	\t\t5. Exit\n\
	\tENTER YOUR CHOICE: ");
	scanf("%d",&ch);
	//char arr[1024];
	//int i=0,j=0;
	getchar();
	switch(ch){
		case 1:
			printf("\n\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n|\t^^^^^^^^^^	DATA SECURITY:TEXT ENCRYPTION DECRYPTION ALONG WITH HUFFMAN ENCODING DECODING	^^^^^^^^^^\t|");
			printf("\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n     Key highlights :\n     ----------------\n");
			printf("\t>>For encoding Decoding we have used Huffman Encryption Decryption Algorithm.\n");
			printf("\t>>For Encryption Decryption we have used RSA Agorithm");
			printf("\t>>Order Of Execution:\
			\n\n\t\t** Encoding----->Encryption----->Decryption----->Decoding **\n");
			

				
			printf("Enter the string:");
			fgets(arr,1024,stdin);
			arr[(strlen(arr)-1)]='\0';   //to remove the enter taken in buffer

			frequency_size(arr);
		 	chr=arr;
			
			struct Node_Heap* root	= HuffmanCode(data,freq,strlen(data));
			//print the hoffman codes for different characters

			printf("\n>>>HOFFMAN CODES:\n");
			print_codes();


			encode(enc);

			printf("\n**********************************************************PERFORMING ENCODING*****************************************************");
			printf("\n\n>>>Encoded Text:%s\t\n",enc);
			
			printf("\n\n********************************************PERFORMING ENCRYPTION AND DECRYPTION**************************************************");
			
			printf("\n\n>>>ENTER THE FIRST PRIME NUMBER: ");
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
			}	 
			
			n=p*q;
			t=(p-1)*(q-1);        //totient
			ce();             //public key(n,e)
			d=cd(); 
		      
			encrypt();
			printf("\n\n>>>THE ENCRYPTED MESSAGE IS:");
				for (i=0;en[i]!=-1;i++)
					printf("%c",en[i]);
			decrypt();
			
			printf("\n\n>>>THE DECRYPTED MESSAGE IS:");
				for (i=0;m[i]!=-1;i++){
				
					printf("%c",m[i]);
			msg[i]=m[i];
			}
			//printf("%d",strlen(m));
			
			//Decoding
			decode(msg,dec,root);  //root has the tree
			
			//fflush(stdout);
			printf("\n\n**********************************************************PERFORMING DECODING*****************************************************");
			printf("\n\n>>>Decoded Text:%s\n",dec);
			printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------\n");
			
			break;
		case 2:
			
			printf("\n\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n|\t^^^^^^^^^^	                        DATA SECURITY:IMAGE ENCRYPTION                             	^^^^^^^^^^\t|");
			printf("\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n     Key highlights :\n     ----------------\n");
			printf("\t>>For encoding Decoding we have used Huffman Encryption Decryption Algorithm.\n");
			printf("\t>>For Encryption Decryption we have used RSA Agorithm");
			printf("\t>>Order Of Execution:\
			\n\n\t\t** Encoding----->Encryption----->Decryption----->Decoding**\n");
						
			    printf("IN IMAGE PART FIRST WE ARE DOING COMPRESSION THEN REST OF THE PROCEDURES\n");
			    printf("WE ARE ONLY USING .BMP IMAGE FORMAT\n");
			    int i, j; 
			    char path[20]; 
			   printf("PLEASE ENTER THE PATH OF AN IMAGE\n");
			   scanf("%[^\n]%*c", &path);  
			     char filename[200];
			//    const char *filename;
			    sprintf( filename, path);
			//    filename="./Sample.bmp";
			    int data = 0, offset, bpp = 0, width, height; 
			    long bmpsize = 0, bmpdataoff = 0; 
			    int** image; 
			    int temp = 0; 
			   
			    // Reading the BMP File 
			    FILE* image_file; 
			      
			    image_file = fopen(filename, "rb");
			//    image_file = fopen("./LAND2.BMP", "rb");
			    printf("%s\n",filename);
			    if (image_file == NULL)  
			    { 
				printf("Error Opening File!!"); 
				exit(1); 
			    } 
			    else
			    {  
					printf("Image is being encrypted..............................\n");  
				// Set file position of the  
				// stream to the beginning 
				// Contains file signature  
				// or ID "BM" 
				offset = 0;    
				// Set offset to 2, which  
				// contains size of BMP File 
				offset = 2; 
			       // printf("step0");   
				fseek(image_file, offset, SEEK_SET); 
			       // printf("step1");   
				//Getting size of BMP File 
				fread(&bmpsize, 4, 1, image_file); 
			       // printf("step2");   
				// Getting offset where the 
				// pixel array starts 
				// Since the information is  
				// at offset 10 from the start,  
				// as given in BMP Header 
				offset = 10;  
				  
				fseek(image_file, offset, SEEK_SET); 
				  
				// Bitmap data offset 
				fread(&bmpdataoff, 4, 1, image_file); 
				  
				// Getting height and width of the image 
				// Width is stored at offset 18 and  
				// height at offset 22, each of 4 bytes 
				fseek(image_file, 18, SEEK_SET); 
				  
				fread(&width, 4, 1, image_file); 
				  
				fread(&height, 4, 1, image_file); 
				  
				// Number of bits per pixel 
				fseek(image_file, 2, SEEK_CUR); 
				  
				fread(&bpp, 2, 1, image_file); 
				  
				// Setting offset to start of pixel data 
				fseek(image_file, bmpdataoff, SEEK_SET); 
				 
				// Creating Image array 
				//printf("done till img array");
				image = (int**)malloc(height * sizeof(int*) +100); 
				for (i = 0; i < height; i++) 
				{ 
				    image[i] = (int*)malloc(width * sizeof(int)+100); 
				} 
				  
				// int image[height][width] 
				// can also be done 
				// Number of bytes in  
				// the Image pixel array 
				int numbytes = (bmpsize - bmpdataoff) / 3;  
				printf("Width of Image: %d",width);
				printf("\nHeight Of Image: %d",height);
				// Reading the BMP File 
				// into Image Array 
				for (i = 0; i < height; i++)  
				{ 
				    for (j = 0; j < width; j++)  
				    { 
					fread(&temp, 3, 1, image_file); 
					  
					// the Image is a  
					// 24-bit BMP Image 
					temp = temp & 0x0000FF;  
					image[i][j] = temp; 
				    } 
				} 
			    } 
			      
			    // Finding the probability 
			    // of occurence 
			    int hist[256]; 
			    for (i = 0; i < 256; i++) 
				hist[i] = 0; 
			    for (i = 0; i < height; i++) 
				for (j = 0; j < width; j++) 
				    hist[image[i][j]] += 1; 
				      
			    // Finding number of  
			    // non-zero occurences 
			    int nodes = 0; 
			    for (i = 0; i < 256; i++) 
				if (hist[i] != 0) 
				    nodes += 1; 
				      
			    // Calculating minimum probability 
			    float p = 1.0, ptemp; 
			    for (i = 0; i < 256; i++)  
			    { 
				ptemp = (hist[i] / (float)(height * width)); 
				if (ptemp > 0 && ptemp <= p) 
				    p = ptemp; 
			    } 
			      
			    // Calculating max length 
			    // of code word 
			    i = 0; 
			    while ((1 / p) > fib(i)) 
				i++; 
			     int maxcodelen = i - 3; 
			      
			    // Defining Structures pixfreq 
			    struct pixfreq 
			    { 
				int pix, larrloc, rarrloc; 
				float freq; 
				struct pixfreq *left, *right; 
				char code[10000]; 
			    }; 
			      
			    // Defining Structures 
			    // huffcode 
			    struct huffcode  
			    { 
				int pix, arrloc; 
				float freq; 
			    }; 
			      
			    // Declaring structs 
			    struct pixfreq* pix_freq; 
			    struct huffcode* huffcodes; 
			    int totalnodes = 2 * nodes - 1; 
			    pix_freq = (struct pixfreq*)malloc(sizeof(struct pixfreq) * totalnodes +100); 
			    huffcodes = (struct huffcode*)malloc(sizeof(struct huffcode) * nodes +100); 
			      
			    // Initializing 
			    j = 0; 
			    int totpix = height * width; 
			    float tempprob; 
			    for (i = 0; i < 256; i++) 
			    { 
				if (hist[i] != 0)  
				{ 
				      
				    // pixel intensity value 
				    huffcodes[j].pix = i;  
				    pix_freq[j].pix = i; 
				      
				    // location of the node 
				    // in the pix_freq array 
				    huffcodes[j].arrloc = j; 
				      
				    // probability of occurrence 
				    tempprob = (float)hist[i] / (float)totpix;  
				    pix_freq[j].freq = tempprob; 
				    huffcodes[j].freq = tempprob; 
				      
				    // Declaring the child of leaf  
				    // node as NULL pointer 
				    pix_freq[j].left = NULL;  
				    pix_freq[j].right = NULL; 
				      
				    // initializing the code  
				    // word as end of line 
				    pix_freq[j].code[0] = '\0';  
				    j++; 
				} 
			    } 
			      
			    // Sorting the histogram 
			    struct huffcode temphuff; 
			      
			    // Sorting w.r.t probability  
			    // of occurence 
			    for (i = 0; i < nodes; i++) 
			    { 
				for (j = i + 1; j < nodes; j++) 
				{ 
				    if (huffcodes[i].freq < huffcodes[j].freq)  
				    { 
					temphuff = huffcodes[i]; 
					huffcodes[i] = huffcodes[j]; 
					huffcodes[j] = temphuff; 
				    } 
				} 
			    } 
			      
			    // Building Huffman Tree 
			    float sumprob; 
			    int sumpix; 
			    int n = 0, k1 = 0; 
			    int nextnode = nodes; 
			      
			    // Since total number of  
			    // nodes in Huffman Tree  
			    // is 2*nodes-1 
			    while (n < nodes - 1)  
			    { 
				  
				// Adding the lowest two probabilities 
				sumprob = huffcodes[nodes - n - 1].freq + huffcodes[nodes - n - 2].freq; 
				sumpix = huffcodes[nodes - n - 1].pix + huffcodes[nodes - n - 2].pix; 
				  
				// Appending to the pix_freq Array 
				pix_freq[nextnode].pix = sumpix; 
				pix_freq[nextnode].freq = sumprob; 
				pix_freq[nextnode].left = &pix_freq[huffcodes[nodes - n - 2].arrloc]; 
				pix_freq[nextnode].right = &pix_freq[huffcodes[nodes - n - 1].arrloc]; 
				pix_freq[nextnode].code[0] = '\0'; 
				i = 0; 
				  
				// Sorting and Updating the  
				// huffcodes array simultaneously 
				// New position of the combined node 
				while (sumprob <= huffcodes[i].freq) 
				      i++; 
				      
				// Inserting the new node  
				// in the huffcodes array 
				for (k1 = nodes; k1 >= 0; k1--)  
				{ 
				    if (k1 == i) 
				    { 
					huffcodes[k1].pix = sumpix; 
					huffcodes[k1].freq = sumprob; 
					huffcodes[k1].arrloc = nextnode; 
				    } 
				    else if (k1 > i) 
				      
					// Shifting the nodes below  
					// the new node by 1 
					// For inserting the new node 
					// at the updated position k 
					huffcodes[k1] = huffcodes[k1 - 1]; 
				      
				} 
				n += 1; 
				nextnode += 1; 
			    } 
			      
			    // Assigning Code through 
			    // backtracking 
			    char left = '0'; 
			    char right = '1'; 
			    int index; 
			    for (i = totalnodes - 1; i >= nodes; i--)  
			    { 
				if (pix_freq[i].left != NULL) 
				    str_cat(pix_freq[i].left->code, pix_freq[i].code, left); 
				if (pix_freq[i].right != NULL) 
				    str_cat(pix_freq[i].right->code, pix_freq[i].code, right); 
			    } 
			      
			    // Encode the Image 
			    int pix_val; 
			    int l; 
			      
			    // Writing the Huffman encoded 
			    // Image into a text file 
			    FILE* imagehuff = fopen("encoded_image.txt", "wb"); 
			    for (i = 0; i < height; i++) {
				for (j = 0; j < width; j++)  
				{ 
				    pix_val = image[i][j]; 
				    for (l = 0; l < nodes; l++) 
					if (pix_val == pix_freq[l].pix) 
					    fprintf(imagehuff, "%s", pix_freq[l].code); 
				    
				} 
				fputs("\n",imagehuff);
				}
				
			       printf("\n\nImage is successfully Encoded!\n\n")   ;
			    // Printing Huffman Codes 
			   // printf("Huffmann Codes::\n\n"); 
			   //printf("pixel values ->   Code\n\n"); 
			    for (i = 0; i < nodes; i++) { 
				if (snprintf(NULL, 0, "%d", pix_freq[i].pix) == 2){ 
			     //       printf("     %d      -> %s\n", pix_freq[i].pix, pix_freq[i].code); 
				    strcat(abcdef,pix_freq[l].code);
			       //     printf("     %s  \n", abcdef);
			       
				}
				else{
				 //   printf("    %d      -> %s\n", pix_freq[i].pix, pix_freq[i].code); 
			    strcat(abcdef,pix_freq[l].code);
			//printf("     %s  \n", abcdef);
			}
			}
			      //char msg[width*height*10]={0};
			    // Calculating Average Bit Length 
			    float avgbitnum = 0; 
			    for (i = 0; i < nodes; i++) 
				avgbitnum += pix_freq[i].freq * codelen(pix_freq[i].code); 
			    printf("Average number of bits:: %f", avgbitnum); 
			   // strcpy(msg, abcdef);
			    //msg[strlen(msg)]='\0';
				/////////////////
				////////////////
				////////////////
				///////////////
			   printf("\nENTER FIRST PRIME NUMBER\n");
			   scanf("%d",&p);
			 
			    flag = prime(p);
			 
			    if(flag==0) {
				printf("\nWRONG INPUT\n");		 
				exit(1);
			    }
			 
			    printf("\nENTER ANOTHER PRIME NUMBER\n");
			    scanf("%d",&q);
			    flag=prime(q);
			    if(flag==0||p==q) {
			 
				printf("\nWRONG INPUT\n");
			 
				
				exit(1);
			 }
			n=3127;
			e=3;            //public key(n,e)
			d=2011; 
			      //printf("%ld %ld, %ld",n,e,d);
			  fclose(imagehuff);
			FILE* fptr=fopen("encoded_image.txt","r");
			FILE* fptr_dec=fopen("decrypted__image.txt","wb");
			FILE* fptr_en=fopen("encryption_image.txt","wb");
			if(fptr==NULL){
			printf("Error opening File");
			break;
			}
			
			ssize_t len1=0;
			long int pt,ct,key=e,k,len,s=0;
			while(fptr && s!=height){
				fgets(msg,807,fptr);
				msg[strlen(msg)]='\0';
				s=s+1;
			      for(i=0;msg[i]!='\0';i++)
					m[i]=msg[i];
			
			printf("%s",msg);
			i=0;
			len=strlen(msg);

			while(i!=len) {
				pt=m[i];
				pt=pt-96;
				k=1;
				for (j=0;j<key;j++) {
					k=k*pt;
					k=k%n;
				}
				//temp[i]=k;
				ct=k+96;
				en[i]=ct;
				i++;
				}
				en[i]=-1;
			//temp[i]=-1;
			//decrypt();
			//printf("\n\n>>>THE ENCRYPTED MESSAGE IS:");
				for (i=0;en[i]!=-1;i++){
			//		printf("%c",en[i]);
					msg[i]=en[i];
				}
					
			fputs(msg,fptr_en);
			fputs("\n",fptr_en);		
			}
	 		printf("\nEncrypted Image file has been saved!\n");
			key=d;
			i=0;
			long int temp1[1024];
			fseek(fptr_en,0,SEEK_SET);
			s=0;
			while(fptr_en && s!=height){
			
			fgets(msg,807,fptr);
			i=0;
			msg[strlen(msg)]='\0';
			while(msg[i]!='\0'){
			en[i]=msg[i];
			m[i]=msg[i];
			i++;
			}
			en[i]=-1;
			i=0;
			s=s+1;
			while(en[i]!=-1) {
			//printf();
			temp1[i]=en[i]-96;
				ct=temp1[i];
				k=1;
				for (j=0;j<key;j++) {
					k=k*ct;
					k=k%n;
			}
			pt=k+96;
			m[i]=pt;
			msg[i]=m[i];
			i++;
				//printf("%ld :::: %ld  ",en[i],m[i]);
			}
			m[i]=-1;
			
			msg[i]='\0';
			fputs(msg,fptr_dec);
			fputs("\n",fptr_dec);	
			}
			
			
	 		/*printf("\n\n>>>THE DECRYPTED MESSAGE IS:");
					for (i=0;msg[i]!='\0';i++){
		
						printf("%c",msg[i]);
				//msg[i]=m[i];
				}*/
	 		printf("\nDecrypted Image file has been saved!\n");
				break;
				
		case 3:
			printf("\n\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n|\t^^^^^^^^^^	                 DATA TRANSMISSION:CHAT ENCRYPTION                     	^^^^^^^^^^\t|");
			printf("\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n Only RSA Encryption is implemented here.\n");
			printf("\n You are the server Now! \n");
			ser_main(argc,argv);
			break;
		case 4:
			printf("\n\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n|\t^^^^^^^^^^	                        MORE INFORMATION OR HELP                             	^^^^^^^^^^\t|");
			printf("\n -----------------------------------------------------------------------------------------------------------------------");
			printf("\n\n\t\t\t\tPROJECT NAME: ENCRYPTION DECRYPTION USING SOCKET PROGRAMMING");
			printf("\n\t\tKEY HIGHLIGHTS OF THE PROJECT:");
			printf("\n\t\t >> It deals with the fast and secure data transmission");
			printf("\n\t\t >> For security we have used Huffman Encoding and Decoding along with RSA encryption");
			printf("\n\t\t >> For transmission we are using RSA Encryption");
			printf("\n\t\t >> It deals with the fast and secure data transmission \n");
			break;
		case 5:
			return 0;
			}

}
