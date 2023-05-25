#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ALIASES 100
#define MAX_ALIAS_NAME_LENGHT 50
#define MAX_ALIAS_VALUE_LENGHT 100
struct Alias{
char name(MAX_ALIAS_NAME_LENGHT);
char value(MAX_ALIAS_VALUE_LENGHT);
};
struct Alias Aliases[MAX_ALIASES];
int numAliases = 0;
void printAliases(){
for (int i = 0; i < numAliases; i++){
printf("%s='%s'\n",aliases[i].name, aliases[i].value);
}
}
void setAlias(char *name char *value){
int index = -1;
//check if alias already exits
for (int i = 0; i < numAliases; i++) {
if (strcmp(aliases[i].name, name) ==0) {
index = i;
break;
}
}
//update or dd the alias
if (inddex != -1){
strcpy(aliases[index].vale, value);}
else{
if (numAliases < MAX_ALIASES){
strcpy(aliases[numAliases].name, name);
strcpy(aliases[numAliases].value, value);
numAliases++
}else {
printf("MAX NUMBER OF ALIASES REACHED\n");
}
}
}
void processAlias(int argc, char argv[]){
if (argc = 0){
printAliases();
}else{
for for (int i = 0; i < argc; i++){
if (strchr(arg[i], '=') != NULL){
char *name strtok(argc[i], '=');
char *value(NULL, '=');
setAlias(ame, value)}
else{
int found = 0;
for (int j = 0; j < numAliases; j++){
if (strcmp(aliases[j].name argv[i]) ==0) {
printf("%s='s'\n" aliases[j].name, aliases[j].value);
found = 1;
break;
}
}
if (!found) {
printf("Alias not found: %s\n" argv[i]);
}
}
}
}
}
int main() {
char command[100];
while (1){
printf("$ ");
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0'; //remove new line caharacter
if (strcmp(command, "exit") ==0){
break;
}
if (strncp(command, "alias" 5) ==0){
char *args[100];
int argc = 0;
char *token = strtok(command +5 " ");
while (token != NULL) {
args[argc++] = token;
token = strtok(NULL, " ");
}
processAlias(argc, args);
}else{
//Execute the command
}
}
return 0;
}
