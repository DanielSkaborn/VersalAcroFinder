#include <stdio.h>

char wordDatabase[1000][1000];
int items = 0;

int strCmp(char *str1, char  *str2) {

	int i=0;
	
	while(1) {
		if (str1[i]!=str2[i])
			return 0;
		if (i==100)
			return 0;
		if ( (str1[i]==0) && (str2[i]==0) )
			return 1;
		i++;
	}
}

int inDb(char *str) {

	int n = 0;
	int i;
    int match;
    match = 0;
	for (n=0;n<items;n++) {
		match = match + strCmp(str, &wordDatabase[n][0]);
	}
	
	if ((match == 0) || (items ==0)) {
		if (items<1000) {
			printf("%d %s\n",items,str);
			for (i=0;i<1000;i++)
				wordDatabase[items][i] = str[i];
			items++;
		}
	}
	return match;
}

void initDb(void) {
	int n;
	items = 0;
	for (n=0;n<1000;n++)
		wordDatabase[n][0] = 0;
		wordDatabase[n][1] = 0;
}


int main (int argc, char *argv[]) {
	
	FILE *infil;
	
	unsigned char rd, state;
	char wordbuffer[1000];
	char filename[1000];
	int wordbuffercnt;
	
	if (argc>=1) {
		sprintf(filename, "%s", argv[1]);
		printf("\n   *** input file: %s\n",filename);
	} else {
		printf("\n    *** give and text file [.rst] as input arfument\n\n");
		return 0;
	}
	
	initDb();
	
	infil = fopen(filename,"r");
	if (infil==NULL) {
		printf("   *** unable to open file\n\n");
		return 0;
	}
	

	state = 0;

	printf("\n");

	while(!feof(infil)) {
		rd=fgetc(infil);
		
		switch (state) {
		
		case 0:
			if (rd==' ')
				state = 1;
			break;
			
		case 1:
			if (rd>='A'&&rd<='Z') {
				wordbuffer[0] = rd;
				wordbuffer[1] = 0;
				wordbuffercnt = 1;
				state = 2;
			}
			break;

		case 2:

            if ( ( wordbuffercnt>1 ) && ( rd==' '  || rd=='.' || rd==',' || rd==';' ) ) { // found VeralAcro...
				if (inDb(wordbuffer)) {
					wordbuffercnt = 0;
				}
				
				if (rd==' ')
					state = 1;
				else
					state = 0;
			} else if ((rd>='A' && rd<='Z') || (rd>='0' && rd<='9')) {
				wordbuffer[wordbuffercnt] = rd;
				wordbuffercnt++;
				wordbuffer[wordbuffercnt] = 0;
				state = 2;
			} else {
				if (rd==' ') state = 1;
				else state = 0; // not valid word
			}
			
			break;
		
		default:
			state = 0;
			break;
			
		}
	}
}
