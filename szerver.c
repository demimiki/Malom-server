#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define INIT_STEPS 9

typedef struct{
	int state;
	int lepesek[4];
}POZ;

POZ jatekter[24];

char tmp[1000];

void init(){
	for(int i=0;i<24;i++){
		jatekter[i].state=0;
		for(int j=0;j<4;j++)
			jatekter[i].lepesek[j]=-1;
	}
	
	jatekter[0].lepesek[0]=1;
	jatekter[0].lepesek[1]=7;
	jatekter[1].lepesek[0]=0;
	jatekter[1].lepesek[1]=2;
	jatekter[1].lepesek[2]=9;
	jatekter[2].lepesek[0]=1;
	jatekter[2].lepesek[1]=3;
	jatekter[3].lepesek[0]=2;
	jatekter[3].lepesek[1]=4;
	jatekter[3].lepesek[2]=11;
	jatekter[4].lepesek[0]=3;
	jatekter[4].lepesek[1]=5;
	jatekter[5].lepesek[0]=4;
	jatekter[5].lepesek[1]=6;
	jatekter[5].lepesek[2]=13;
	jatekter[6].lepesek[0]=5;
	jatekter[6].lepesek[1]=7;
	jatekter[7].lepesek[0]=0;
	jatekter[7].lepesek[1]=6;
	jatekter[7].lepesek[2]=15;
	
	jatekter[8].lepesek[0]=9;
	jatekter[8].lepesek[1]=15;
	jatekter[9].lepesek[0]=8;
	jatekter[9].lepesek[1]=10;
	jatekter[9].lepesek[2]=1;
	jatekter[9].lepesek[3]=17;
	jatekter[10].lepesek[0]=9;
	jatekter[10].lepesek[1]=11;
	jatekter[11].lepesek[0]=10;
	jatekter[11].lepesek[1]=12;
	jatekter[11].lepesek[2]=3;
	jatekter[11].lepesek[3]=19;
	jatekter[12].lepesek[0]=11;
	jatekter[12].lepesek[1]=13;
	jatekter[13].lepesek[0]=12;
	jatekter[13].lepesek[1]=14;
	jatekter[13].lepesek[2]=5;
	jatekter[13].lepesek[3]=21;
	jatekter[14].lepesek[0]=13;
	jatekter[14].lepesek[1]=15;
	jatekter[15].lepesek[0]=8;
	jatekter[15].lepesek[1]=14;
	jatekter[15].lepesek[2]=7;
	jatekter[15].lepesek[3]=23;
	
	jatekter[16].lepesek[0]=17;
	jatekter[16].lepesek[1]=23;
	jatekter[17].lepesek[0]=16;
	jatekter[17].lepesek[1]=18;
	jatekter[17].lepesek[2]=9;
	jatekter[18].lepesek[0]=17;
	jatekter[18].lepesek[1]=19;
	jatekter[19].lepesek[0]=18;
	jatekter[19].lepesek[1]=20;
	jatekter[19].lepesek[2]=11;
	jatekter[20].lepesek[0]=19;
	jatekter[20].lepesek[1]=21;
	jatekter[21].lepesek[0]=20;
	jatekter[21].lepesek[1]=22;
	jatekter[21].lepesek[2]=13;
	jatekter[22].lepesek[0]=21;
	jatekter[22].lepesek[1]=23;
	jatekter[23].lepesek[0]=16;
	jatekter[23].lepesek[1]=22;
	jatekter[23].lepesek[2]=15;
}

int checkTable(int p, int lep){
	//külső gyűrű
	if(lep==0 || lep==1 || lep==2)
		if(jatekter[0].state==p && jatekter[1].state==p && jatekter[2].state==p) return 1;	
	if(lep==2 || lep==3 || lep==4)
		if(jatekter[2].state==p && jatekter[3].state==p && jatekter[4].state==p) return 1;
	if(lep==4 || lep==5 || lep==6)
		if(jatekter[4].state==p && jatekter[5].state==p && jatekter[6].state==p) return 1;
	if(lep==6 || lep==7 || lep==0)
		if(jatekter[6].state==p && jatekter[7].state==p && jatekter[0].state==p) return 1;
		//középső gyűrű
	if(lep==8 || lep==9 || lep==10)
		if(jatekter[8].state==p && jatekter[9].state==p && jatekter[10].state==p) return 1;
	if(lep==10 || lep==11 || lep==12)
		if(jatekter[10].state==p && jatekter[11].state==p && jatekter[12].state==p) return 1;
	if(lep==12 || lep==13 || lep==14)
		if(jatekter[12].state==p && jatekter[13].state==p && jatekter[14].state==p) return 1;
	if(lep==14 || lep==15 || lep==8)
		if(jatekter[14].state==p && jatekter[15].state==p && jatekter[8].state==p) return 1;
		//belső gyűrű
	if(lep==16 || lep==17 || lep==18)
		if(jatekter[16].state==p && jatekter[17].state==p && jatekter[18].state==p) return 1;
	if(lep==18 || lep==19 || lep==20)
		if(jatekter[18].state==p && jatekter[19].state==p && jatekter[20].state==p) return 1;
	if(lep==20 || lep==21 || lep==22)
		if(jatekter[20].state==p && jatekter[21].state==p && jatekter[22].state==p) return 1;
	if(lep==22 || lep==23 || lep==16)
		if(jatekter[22].state==p && jatekter[23].state==p && jatekter[16].state==p) return 1;
		//összekötők
	if(lep==1 || lep==9 || lep==17)
		if(jatekter[1].state==p && jatekter[9].state==p && jatekter[17].state==p) return 1;
	if(lep==3 || lep==11 || lep==19)
		if(jatekter[3].state==p && jatekter[11].state==p && jatekter[19].state==p) return 1;
	if(lep==5 || lep==13 || lep==21)
		if(jatekter[5].state==p && jatekter[13].state==p && jatekter[21].state==p) return 1;
	if(lep==7 || lep==15 || lep==23)
		if(jatekter[7].state==p && jatekter[15].state==p && jatekter[23].state==p) return 1;
		
	return 0;
}

int isValidMove(int from_coord, int to_coord){
	if(from_coord<0 || from_coord>23 || to_coord<0 || from_coord>23)
		return 0;
	if(jatekter[to_coord].state!=0)
		return 0;
	for(int i=0;i<4;i++)
		if(jatekter[from_coord].lepesek[i]==to_coord)
			return 1;	
	return 0;
}

int isEmptySpace(int place){
	if(place>23 || place<0)
		return 0;
	if(jatekter[place].state!=0)
		return 0;
	return 1;
}

char* getTableToSendMsg(){
	tmp[0]='\0';
	
	for(int i=0;i<24;i++){
		if(jatekter[i].state==0)
			strcat(tmp,"0");
		if(jatekter[i].state==1)
			strcat(tmp,"1");
		if(jatekter[i].state==2)
			strcat(tmp,"2");
		strcat(tmp,",");
	}
	return tmp;
}

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Ervenytelen argumentum!\n");
		return 0;
	}
	init();
	
	int sikeres, on=1;
	struct sockaddr_in serveraddress;
	int serversocket = socket(AF_INET, SOCK_STREAM, 0);
	serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(atoi(argv[1]));
    serveraddress.sin_addr.s_addr = INADDR_ANY;
	
	setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
    setsockopt(serversocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);
	
	sikeres = bind(serversocket, (struct sockaddr *) &serveraddress, sizeof(serveraddress));
	if(sikeres==-1){
		fprintf(stderr,"Hiba \"bind\" soran\n");
		return 0;
	}
	
	sikeres = listen(serversocket, 2);
	if(sikeres==-1){
		fprintf(stderr,"Hiba \"listen\" soran\n");
		return 0;
	}
	
	printf("Varakozas jatekosok csatlakozasara\n");
	
	char uzenet[1000];
	int kliens_azon[2];
	for(int i=1;i<=2;i++){
		printf("Varakozas a(z) %d. jatekos csatlakozasara\n",i);
		kliens_azon[i-1]=accept(serversocket,NULL,NULL);
		if(kliens_azon[i-1]==-1){
			fprintf(stderr,"Hiba \"accept\" soran\n");
			return 0;
		}
		printf("A(z) %d. jatekos csatlakozott\n",i);
		sprintf(uzenet,"%d",i);
		sikeres=send(kliens_azon[i-1],uzenet,sizeof(uzenet),0);
		if(sikeres==-1){
			fprintf(stderr,"Hiba \"send\" soran\n");
			return 0;
		}
		uzenet[0]='\0';
	}
	
	int ok;
	//feltöltés játékosoktól
	for(int i=0;i<INIT_STEPS;i++){
		for(int j=0;j<2;j++){
			ok=0;
			sprintf(uzenet,"%d",i+1);
			sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Kör
			if(sikeres==-1){
				fprintf(stderr,"Hiba \"send\" soran\n");
				return 0;
			}
			
			strcpy(uzenet,getTableToSendMsg());
			sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Tábla
			if(sikeres==-1){
				fprintf(stderr,"Hiba \"send\" soran\n");
				return 0;
			}
			
			while(!ok){
				sikeres=recv(kliens_azon[j], &uzenet, sizeof(uzenet), 0);//Mező
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"recv\" soran\n");
					return 0;
				}			
				if(isEmptySpace(atoi(uzenet))){
					jatekter[atoi(uzenet)].state=j+1;
					printf("State changed: %d field to %d\n",atoi(uzenet),j+1);
					ok=1;
					sprintf(uzenet,"1");
					sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Válasz
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
					
					strcpy(uzenet,getTableToSendMsg());
					sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Tábla
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
				}
				else{
					sprintf(uzenet,"-1");
					sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
				}
			}
		}
	}
	
	
	uzenet[0]='\0';
	printf("Sending table to players\n");
	strcpy(uzenet,getTableToSendMsg());
	
	sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);
	if(sikeres==-1){
		fprintf(stderr,"Hiba \"send\" soran\n");
		return 0;
	}	
	sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);
	if(sikeres==-1){
		fprintf(stderr,"Hiba \"send\" soran\n");
		return 0;
	}	
	
	
	//////////////////////////////////////////////////////////
	int korszamlalo=0;
	int p1_babu=INIT_STEPS, p2_babu=INIT_STEPS;
	while(1){
		for(int j=0;j<2;j++){
			printf("The %d. player is next\n",j+1);
			sprintf(uzenet,"%s",getTableToSendMsg());
			sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Tábla
			if(sikeres==-1){
				fprintf(stderr,"Hiba \"send\" soran\n");
				return 0;
			}
			//CHECK: DRAW, LOSE, WIN(then send it here)
			if(korszamlalo>13){
				if(p1_babu>p2_babu){
					sprintf(uzenet,"WIN");
					sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
					sprintf(uzenet,"LOSE");
					sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
				}
				if(p1_babu<p2_babu){
					sprintf(uzenet,"LOSE");
					sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
					sprintf(uzenet,"WIN");
					sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
				}
				if(p1_babu==p2_babu){
					sprintf(uzenet,"DRAW");
					sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
					sprintf(uzenet,"DRAW");
					sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
				}
				printf("The game is over\n");
				return 0;
			}
			
			if(p1_babu<=2){				
				sprintf(uzenet,"LOSE");
				sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"send\" soran\n");
					return 0;
				}
				sprintf(uzenet,"WIN");
				sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"send\" soran\n");
					return 0;
				}
				printf("The game is over\n");
				return 0;
			}
			if(p2_babu<=2){				
				sprintf(uzenet,"WIN");
				sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"send\" soran\n");
					return 0;
				}
				sprintf(uzenet,"LOSE");
				sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"send\" soran\n");
					return 0;
				}	
				printf("The game is over\n");
				return 0;
			}
			
			
			sprintf(uzenet,"START");
			sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Jelez a játékosnak, hogy ő következik
			if(sikeres==-1){
				fprintf(stderr,"Hiba \"send\" soran\n");
				return 0;
			}
			int ok=0;
			while(!ok){
				sikeres=recv(kliens_azon[j], &uzenet, sizeof(uzenet), 0);//válasz a klienstől(FELADOM,LEP(x,y))
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"recv\" soran\n");
					return 0;
				}
								
				if(strcmp(uzenet,"FELADOM")==0){
					printf("A jatekot a %d. kliens feladta\n",j+1);
					if(j==0){
						sprintf(uzenet,"GAVE_UP");
						sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);
						if(sikeres==-1){
							fprintf(stderr,"Hiba \"send\" soran\n");
							return 0;
						}
						sprintf(uzenet,"OTHER_GAVE_UP");
						sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);
						if(sikeres==-1){
							fprintf(stderr,"Hiba \"send\" soran\n");
							return 0;
						}
						printf("A jatek veget ert.\n");
						return 0;
					}
					else{
						sprintf(uzenet,"GAVE_UP");
						sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);
						if(sikeres==-1){
							fprintf(stderr,"Hiba \"send\" soran\n");
							return 0;
						}
						sprintf(uzenet,"OTHER_GAVE_UP");
						sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);
						if(sikeres==-1){
							fprintf(stderr,"Hiba \"send\" soran\n");
							return 0;
						}
						printf("A jatek veget ert.\n");
						return 0;
					}
				}
				else{//LEPES lesz, forma:LEP,FROM,TO
					//NO,MALOM,OK
					int failed=0;
					char* token;
					int from_koord,to_koord;
					token = strtok(uzenet, ","); 
					from_koord=atoi(strtok(NULL,","));
					to_koord=atoi(strtok(NULL,","));
					
					int lepes=0;
					char* tmp;
					while(!lepes){
						if(failed){
							token = strtok(uzenet, ","); 
							tmp=strtok(NULL,",");
							if(strcmp(tmp,"FELADOM")==0){
								printf("A jatekot a %d. kliens feladta\n",j+1);
								if(j==0){
									sprintf(uzenet,"GAVE_UP");
									sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);
									if(sikeres==-1){
										fprintf(stderr,"Hiba \"send\" soran\n");
										return 0;
									}
									sprintf(uzenet,"OTHER_GAVE_UP");
									sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);
									if(sikeres==-1){
										fprintf(stderr,"Hiba \"send\" soran\n");
										return 0;
									}
									printf("A jatek veget ert.\n");
									return 0;
								}
								else{
									sprintf(uzenet,"GAVE_UP");
									sikeres=send(kliens_azon[1],uzenet,sizeof(uzenet),0);
									if(sikeres==-1){
										fprintf(stderr,"Hiba \"send\" soran\n");
										return 0;
									}
									sprintf(uzenet,"OTHER_GAVE_UP");
									sikeres=send(kliens_azon[0],uzenet,sizeof(uzenet),0);
									if(sikeres==-1){
										fprintf(stderr,"Hiba \"send\" soran\n");
										return 0;
									}
									printf("A jatek veget ert.\n");
									return 0;
								}
							}
							from_koord=atoi(tmp);
							to_koord=atoi(strtok(NULL,","));
							failed=0;
						}
						int valos=isValidMove(from_koord,to_koord);
						printf("The %d. player want to step from %d to %d\n",j+1,from_koord,to_koord);
						if(jatekter[from_koord].state!=j+1)
							valos=0;
						if(!valos){
							sprintf(uzenet,"NO");
							sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Nem érvényes lépés
							if(sikeres==-1){
								fprintf(stderr,"Hiba \"send\" soran\n");
								return 0;
							}
							failed=1;
							uzenet[0]='\0';
							printf("Invalid move detected from %d. player\n",j+1);
							sikeres=recv(kliens_azon[j], &uzenet, sizeof(uzenet), 0);//újrakérjük a lépést
							if(sikeres==-1){
								fprintf(stderr,"Hiba \"recv\" soran\n");
								return 0;
							}
						}					
						else{
							lepes=1;
							printf("Move accepted!\n");
							jatekter[from_koord].state=0;
							jatekter[to_koord].state=j+1;
							
							
							int malom=checkTable(j+1,to_koord);
							if(malom){
								printf("MALOM detected\n");
								sprintf(uzenet,"MALOM");
								sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//MALOM
								if(sikeres==-1){
									fprintf(stderr,"Hiba \"send\" soran\n");
									return 0;
								}
								int ok2=0;
								while(!ok2){
									sikeres=recv(kliens_azon[j], &uzenet, sizeof(uzenet), 0);//válasz a klienstől(x) malomnál
									if(sikeres==-1){
										fprintf(stderr,"Hiba \"recv\" soran\n");
										return 0;
									}
									int x=atoi(uzenet);
									printf("Got %d to remove\n",x);
									if(j==0){//1.player
										if(jatekter[x].state==2 && !jatekter[x].state==0){//OK lépés
											jatekter[x].state=0;//levesz ellenfél bábúja
											p2_babu--;
											printf("%d removed\n",x);
											sprintf(uzenet,"OK");
											sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//OK
											if(sikeres==-1){
												fprintf(stderr,"Hiba \"send\" soran\n");
												return 0;
											}
											sprintf(uzenet,"%s",getTableToSendMsg());
											sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Tábla
											if(sikeres==-1){
												fprintf(stderr,"Hiba \"send\" soran\n");
												return 0;
											}
											ok=1;
											ok2=1;
										}
										else{
											printf("Remove not possible\n");
											sprintf(uzenet,"NO");
											sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Nem érvényes lépés
											if(sikeres==-1){
												fprintf(stderr,"Hiba \"send\" soran\n");
												return 0;
											}
										}
									}
									else{//2.player
										if(jatekter[x].state==1 && !jatekter[x].state==0){//OK lépés
											jatekter[x].state=0;//levesz ellenfél bábúja
											p1_babu--;
											printf("%d removed\n",x);
											sprintf(uzenet,"OK");
											sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//OK
											if(sikeres==-1){
												fprintf(stderr,"Hiba \"send\" soran\n");
												return 0;
											}
											sprintf(uzenet,"%s",getTableToSendMsg());
											sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Tábla
											if(sikeres==-1){
												fprintf(stderr,"Hiba \"send\" soran\n");
												return 0;
											}
											ok=1;
											ok2=1;
										}
										else{
											printf("Remove not possible\n");
											sprintf(uzenet,"NO");
											sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Nem érvényes lépés
											if(sikeres==-1){
												fprintf(stderr,"Hiba \"send\" soran\n");
												return 0;
											}
										}
									}
									korszamlalo=-1;
								}
							}
							else{//NINCS MALOM
								ok=1;
								printf("No MALOM, continue\n");
								sprintf(uzenet,"OK");
								sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//OK
								if(sikeres==-1){
									fprintf(stderr,"Hiba \"send\" soran\n");
									return 0;
								}
								sprintf(uzenet,"%s",getTableToSendMsg());
								sikeres=send(kliens_azon[j],uzenet,sizeof(uzenet),0);//Tábla
								if(sikeres==-1){
									fprintf(stderr,"Hiba \"send\" soran\n");
									return 0;
								}
							}
						}
					}
				}
			}
		}
		korszamlalo++;
	}
	
	return 0;
}
