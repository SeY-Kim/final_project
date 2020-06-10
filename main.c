#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define STRING_SIZE 256

//21300858 YOUNGJAE KIM
//This program gets data from internet and collect those data into one html file. 
int time = 0;

int main(){
	
	//loop every 30 seconds
	while(1) {
	printf("Program Started...\n");
	
	printf("websites downloading... \n");
		
	//html file download from corona real time data website and rename to corona.html
	system("wget en.wikipedia.org/wiki/COVID-19_pandemic_in_South_Korea");
	system("mv COVID-19_pandemic_in_South_Korea corona.html");	
	
	//temprature html download
	system("wget meteocast.net/forecast/kr/pohang");	
	system("mv pohang weather.html");
	
	//fopen the downloaded html file
	FILE* fp_corona,* fp_weather;
	FILE* fp_final;


	if ((fp_corona = fopen("corona.html","r")) ==NULL) {
		printf("error reading corona.html\n");
		return 0;
	}	
	
	char buf[1000];
	char data[100][1000];
	

	for(int i = 0; i < 80; i++){
	fgets(buf,sizeof(buf),fp_corona);
//	printf("%s\n",buf);
	strcpy(data[i],buf);
	}
//	printf("this -> %s\n", data+64);
//	printf("this - > %s\n", data+65);

	fp_final = fopen("corona_real_time.html","w");
	fprintf(fp_final, "<HTML>\n<HEAD>CORONA REAL TIME (South Korea)</HEAD>\n<BODY> <table>%s%s </BODY>\n</HTML>",data+64,data+65);
	fclose(fp_final);
	
	system("cp corona_real_time.html /var/www/html");
	fclose(fp_corona);

	//weather data get
	if((fp_weather =  fopen("weather.html","r"))==NULL){
		printf("error");
		return 0;
	}
	char buf2[1000];
	char data2[100][1000];
	for(int i = 0; i<80; i++){
		fgets(buf2,sizeof(buf2),fp_weather);
		strcpy(data2[i],buf2);
	}
	
//	printf("%s\n", data2+44);
//	printf("%s\n", data2+45);
//	printf("%s\n", data2+46);


	fp_final = fopen("weather_real_time.html","w");
	fprintf(fp_final, "<HTML>\n<HEAD>WEATHER REAL TIME (Pohang)</HEAD>\n<BODY> %s%s%s%s </BODY>\n</HTML>",data2+44,data2+45,data2+46,data2+47);
	fclose(fp_final);

	system("cp weather_real_time.html /var/www/html");
	fclose(fp_weather);

	//wait for 30 seconds before updates

	sleep(30);

	}//while loop end

	return 0;
}
