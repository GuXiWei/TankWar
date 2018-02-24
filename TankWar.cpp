#pragma warning(disable:4996)
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#define BLOCK 1
#define FREE 0
#define OK 0
#define ER -1
#define true 1
#define false 0
#define SPEED 20000				//̹���˶��ٶȣ���ֵԽС���ٶ�Խ��
#define SPEED_BULLET 2000  		//�ڵ��˶��ٶȣ�����ԽС���ٶ�Խ��
#define Status int
#define STRAIGHT 85				//������ֱ�ߵĸ���
#define BIU 15					//�����˷��ӵ��ĸ���

#if 1
typedef struct BULLET{
	int x;
	int y;
	char dir;
	int speed;
	struct BULLET *next;
}Bullet;
typedef struct TANK{
	int x;
	int y;
	char dir;
	int shape[3][3];
	Bullet *bullink;
}Tank;
typedef struct MAP{
	int **a;
	int length;
}Map;
typedef struct TANDNODE{
	Tank *tank;
	struct TANDNODE *next;
}Tanknode;
typedef struct TANKLINK{
	Tanknode *tanklink;
	int tank_num;
}Tanklink;

Status InitMap(Map *map, char *filename);
//��ʼ����ͼ,Ϊmap���䶯̬���飬����Ϊfilename�ĵ�ͼ�ļ��ж�ȡ��ͼ
Status DestroyMap(Map *map);
//���ٵ�ͼ,��map������0�����ɹ����ٷ���OK����map�����Ѿ���0�򷵻�ER
void PrintMap(Map map);
//��ӡ��ͼ
Status InitTank(Tank **tank, int x, int y, char dir);
//��ʼ��̹�ˣ�����ռ䣬ָ�������뷽�򣬳�ʼ������״����Ϊ�ӵ���������ͷָ��
Status DestroyTank(Tank **tank);
//����̹�ˣ�����tank������Ϊ(-1,-1),dirΪ0������ӵ������ɹ����ٷ���OK�����򷵻�ER
void PrintTank(Tank tank);
//��ӡ̹��
void ClearTank(Tank tank);
//���̹��
Status canPutTank(Tank tank, Map map);
//�ж�̹�˴�ʱ��λ���ڵ�ͼ���Ƿ�Ϸ�
Status ChangeDir(Tank *tank, char dir);
//�ı�̹�˵ķ������״
Status canMoveTank(Tank tank, Map map);
//�жϴ�ʱ��̹���Ƿ��ű����ķ����ƶ�һ��
Status canChangeDir(Tank tank, Map map, char dir);
//�жϴ�ʱ��̹���ܷ�ı䷽��
Status ChangeTankDir(Tank *tank, Map map, char dir);
//�ı�̹�˷������޷��ı䷵��ER,����ı�̹�˷������״����ӡ������OK
Status MoveTank(Tank *tank, Map map);
//�ƶ�̹�ˣ����޷��ƶ�̹�ˣ��򷵻�ER������ı�̹�����겢��ӡ������OK
Status InitBullet(Bullet *bul, int x, int y, char dir);
//��ʼ���ӵ���ָ������ͷ���
void ClearBullet(Bullet bul);
//����ӵ�
Status InsertBullet(Bullet *bullink, Bullet *bul);
//���ӵ�bul�����ӵ�����bullinkĩβ���ɹ����뷵��OK�����򷵻�ER
Status DeleteBullet(Bullet *bullink, Bullet *bul);
//���ӵ�bul���ӵ�����bullink��ɾ������bul��bullink�����ڻ�ɾ��ʧ�ܣ�����ER�����򷵻�OK
int BulletNum(Bullet *bullink);
//�����ӵ����������ӵ�����bullink�ĳ���
Status CreatBullet(Tank *tank);
//ģ��̹��tank�����ӵ�������һ���ӵ���������ӡ��ֻ�ǳ�ʼ�����ѣ�
void PrintBullet(Bullet bul);
//��ӡ�ӵ�
Status canPutBullet(Bullet bul, Map map);
//�ж��ӵ���ǰλ�ô��ڵ�ͼ��ʲô�ϰ�����
Status canMoveBullet(Bullet bul, Map map);
//�ж��ӵ��ܷ񳯵�ǰ�����ƶ�һ��
Status MoveBullet(Bullet *bul, Tank *tank, Map *map);
//�ƶ��ӵ������ǿյأ��ƶ�һ���������ϰ�����ϰ���ͬ���ھ�������ǽ�ڣ������ӵ�
Status MoveTankBullet(Tank *tank, Map *map);
//�ƶ�һ��̹�˵������ӵ�
Status isBulletInTank(Bullet bul, Tank tank);
//�ж��ӵ��Ƿ����̹��
Status InitTankLink(Tanklink *tanklink);
//��ʼ��̹�˶��У������䳤��Ϊ0����Ϊ�������ͷָ��
Status DestroyTankLink(Tanklink *tanklink);
//����̹�˶��У������䳤��Ϊ0���һ�������ͷָ��
Status ClearTankLink(Tanklink *tanklink);
//���̹�˶����е�����̹�ˣ�ʹ��ֻʣ����ͷָ�룬�䳤��Ϊ0
Status DeleteTank(Tanklink *tanklink, Tank **tank);
//ɾ��̹�˶�����ָ����tank̹��
Status InsertTank(Tanklink *tanklink, Tank *tank);
//��̹�˶���tanklink�в���ָ��tank̹�˵Ľڵ�
Status TankLinkTraverse(Tanklink tlink, void(*visit)(Tank));
//�����������
Status AutoTank(Tank *tank, Map *map);
//ģ��̹���Զ��ƶ��뷢���ӵ�

int MainMenu();
void PrintMainMenu();
void PrintHelp();
void PrintAbout();

void HideCursor();
//���ع��
void PutCursor();
//��ʾ���
void GotoXy(int x, int y);
//������ƶ���(X,Y)
void GetXy(int *X, int *Y, int x1, int x2, int y1, int y2);
//��ȡ���޶���Χ�������������

void HideCursor(){								 //���ع��
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void PutCursor(){								 //��ʾ���
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void GotoXy(int x, int y){						 //������ƶ���(X,Y)
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GetXy(int *X, int *Y, int x1, int x2, int y1, int y2){ //��ȡ���޶���Χ�������������
	HANDLE hInput;                              //��ȡ��׼�����豸���
	INPUT_RECORD inRec;                         //�������ݼ�¼
	DWORD res;                                  //�����Ѷ�ȡ�ļ�¼��
	int x = -1, y = -1;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	do{
		ReadConsoleInput(hInput, &inRec, 1, &res);
		if (inRec.EventType == MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
			x = (int)inRec.Event.MouseEvent.dwMousePosition.X;
			y = (int)inRec.Event.MouseEvent.dwMousePosition.Y;
		}
	} while (!(x >= x1&&x <= x2&&y >= y1&&y <= y2));
	*X = x;
	*Y = y;
}
Status InitMap(Map *map, char *filename){
	int i, j;
	int num_read;
	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp)return ER;
	num_read = fscanf(fp, "%d", &map->length);
	if (num_read < 0)return ER;
	map->a = (int**)malloc(sizeof(int*)*map->length);
	for (i = 0; i < map->length; i++){
		map->a[i] = (int*)malloc(sizeof(int)*map->length);
		if (!map->a[i])return ER;
		for (j = 0; j < map->length; j++){
			num_read = fscanf(fp, "%1d", &map->a[i][j]);
			if (num_read < 0)return ER;
		}
	}
	return OK;
}
Status DestroyMap(Map *map){
	int i, j;
	if (map->length == 0 || map->a == NULL)return ER;
	for (i = 0; i < map->length; i++)free(map->a[i]);
	free(map->a);
	map->length = 0;
	map->a = NULL;
	return OK;
}
void PrintMap(Map map){
	int i, j;
	int length = map.length;
	for (i = 0; i < length; i++){
		for (j = 0; j < length; j++){
			if (map.a[i][j] == 1)printf("��");
			else if (map.a[i][j] == 0)printf("  ");
			else if (map.a[i][j] == 2)printf("��");
			else if (map.a[i][j] == 3)printf("��");
		}
		printf("\n");
	}
}
void PrintTank(Tank tank){
	int y = tank.y - 1;
	int x = 2 * tank.x - 2;
	int i, j;
	GotoXy(2 * tank.x - 2, y);
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			if (tank.shape[i][j] == 0)GotoXy(x + 2, y);
			else if (tank.shape[i][j] == 1)printf("��");
			x += 2;
		}
		y++;
		x = 2 * tank.x - 2;
		GotoXy(2 * tank.x - 2, y);
	}
}
Status canPutTank(Tank tank, Map map){
	int i, j;
	int x, y;
	int turn;
	turn = true;
	//�ж�-gxw
	if (tank.x < 1 || tank.y < 1 || tank.x >(map.length - 3) || tank.y >(map.length - 3))
	{
		turn = false;
		return turn;
	}
	x = tank.x - 1;
	y = tank.y - 1;
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			if (tank.shape[i][j] == 1){
				if (map.a[y + i][x + j] != 0)turn = false;
			}
		}
	}
	return turn;
}
Status ChangeDir(Tank *tank, char dir){
	if (tank->dir == dir)return ER;
	tank->dir = dir;
	if (dir == 'w'){
		tank->shape[0][0] = 0;
		tank->shape[0][1] = 1;
		tank->shape[0][2] = 0;
		tank->shape[1][0] = 1;
		tank->shape[1][1] = 1;
		tank->shape[1][2] = 1;
		tank->shape[2][0] = 1;
		tank->shape[2][1] = 0;
		tank->shape[2][2] = 1;
	}
	else if (dir == 'd'){
		tank->shape[0][0] = 1;
		tank->shape[0][1] = 1;
		tank->shape[0][2] = 0;
		tank->shape[1][0] = 0;
		tank->shape[1][1] = 1;
		tank->shape[1][2] = 1;
		tank->shape[2][0] = 1;
		tank->shape[2][1] = 1;
		tank->shape[2][2] = 0;
	}
	else if (dir == 's'){
		tank->shape[0][0] = 1;
		tank->shape[0][1] = 0;
		tank->shape[0][2] = 1;
		tank->shape[1][0] = 1;
		tank->shape[1][1] = 1;
		tank->shape[1][2] = 1;
		tank->shape[2][0] = 0;
		tank->shape[2][1] = 1;
		tank->shape[2][2] = 0;
	}
	else if (dir == 'a'){
		tank->shape[0][0] = 0;
		tank->shape[0][1] = 1;
		tank->shape[0][2] = 1;
		tank->shape[1][0] = 1;
		tank->shape[1][1] = 1;
		tank->shape[1][2] = 0;
		tank->shape[2][0] = 0;
		tank->shape[2][1] = 1;
		tank->shape[2][2] = 1;
	}
	return OK;
}
Status canChangeDir(Tank tank, Map map, char dir){
	if (ChangeDir(&tank, dir) == ER)return true;
	else return canPutTank(tank, map);
}
Status InitTank(Tank **tank, int x, int y, char dir){
	int i;
	if (tank == NULL)return ER;
	*tank = (Tank*)malloc(sizeof(Tank));
	if (!*tank)return ER;
	(*tank)->x = x;
	(*tank)->y = y;
	ChangeDir((*tank), dir);
	(*tank)->bullink = (Bullet *)malloc(sizeof(Bullet));
	(*tank)->bullink->next = NULL;
	(*tank)->bullink->x = -1;
	(*tank)->bullink->y = -1;
	(*tank)->bullink->speed = 0;
	(*tank)->bullink->dir = 0;
	if (!(*tank)->bullink)return ER;
	return OK;
}
Status DestroyTank(Tank **tank){
	Bullet *ptr;
	Bullet *temp;
	if (tank == NULL || *tank == NULL)return ER;
	ptr = (*tank)->bullink;
	while (ptr){
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
	*tank = NULL;
	return OK;
}
Status canMoveTank(Tank tank, Map map){
	switch (tank.dir){
	case 'a':tank.x--; break;
	case 'd':tank.x++; break;
	case 'w':tank.y--; break;
	case 's':tank.y++; break;
	}
	return canPutTank(tank, map);
}
void ClearTank(Tank tank){
	int y = tank.y - 1;
	int x = 2 * tank.x - 2;
	int i, j;
	GotoXy(2 * tank.x - 2, y);
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			if (tank.shape[i][j] == 0)GotoXy(x + 2, y);
			else if (tank.shape[i][j] == 1)printf("  ");
			x += 2;
		}
		y++;
		x = 2 * tank.x - 2;
		GotoXy(2 * tank.x - 2, y);
	}
}
Status MoveTank(Tank *tank, Map map){
	if (canMoveTank(*tank, map) == false)return ER;
	ClearTank(*tank);
	switch (tank->dir){
	case 'a':tank->x--; break;
	case 'd':tank->x++; break;
	case 'w':tank->y--; break;
	case 's':tank->y++; break;
	}
	PrintTank(*tank);
	return OK;
}
Status ChangeTankDir(Tank *tank, Map map, char dir){
	if (tank->dir == dir)return ER;
	if (canChangeDir(*tank, map, dir) == true){
		ClearTank(*tank);
		ChangeDir(tank, dir);
		PrintTank(*tank);
		return OK;
	}
	else{
		Tank *tank_tmp;
		if (InitTank(&tank_tmp, tank->x, tank->y, dir) == ER)return ER;
		switch (dir){
		case 'a':tank_tmp->x--; break;
		case 'd':tank_tmp->x++; break;
		case 'w':tank_tmp->y--; break;
		case 's':tank_tmp->y++; break;
		}
		if (canPutTank(*tank_tmp, map) == false){
			DestroyTank(&tank_tmp);
			return ER;
		}
		else{
			ClearTank(*tank);
			tank->x = tank_tmp->x;
			tank->y = tank_tmp->y;
			ChangeDir(tank, tank_tmp->dir);
			PrintTank(*tank);
			DestroyTank(&tank_tmp);
			return OK;
		}
	}
}
Status InitBullet(Bullet *bul, int x, int y, char dir){
	if (bul == NULL)return ER;
	bul->x = x;
	bul->y = y;
	bul->dir = dir;
	bul->speed = SPEED_BULLET;
	bul->next = NULL;
	return OK;
}
Status InsertBullet(Bullet *bullink, Bullet *bul){
	Bullet *ptr;
	if (!bullink || !bul)return ER;
	for (ptr = bullink; ptr->next; ptr = ptr->next);
	ptr->next = bul;
	bul->next = NULL;
	return OK;
}
Status DeleteBullet(Bullet *bullink, Bullet *bul){
	Bullet *ptr;
	if (!bullink || !bul)return ER;
	for (ptr = bullink; ptr && ptr->next != bul; ptr = ptr->next);
	if (ptr == NULL)return ER;
	else{
		ptr->next = bul->next;
		free(bul);
		bul = NULL;
	}
	return OK;
}
int BulletNum(Bullet *bullink){
	Bullet *ptr;
	int num;
	if (bullink == NULL)return ER;
	for (num = 0, ptr = bullink->next; ptr; ptr = ptr->next, num++);
	return num;
}
Status CreatBullet(Tank *tank){
	Bullet *bul;
	if (tank == NULL || tank->bullink == NULL)return ER;
	bul = (Bullet*)malloc(sizeof(Bullet));
	if (!bul)return ER;
	switch (tank->dir){
	case 'a':InitBullet(bul, tank->x - 1, tank->y, 'a'); break;
	case 'd':InitBullet(bul, tank->x + 1, tank->y, 'd'); break;
	case 'w':InitBullet(bul, tank->x, tank->y - 1, 'w'); break;
	case 's':InitBullet(bul, tank->x, tank->y + 1, 's'); break;
	}
	if (InsertBullet(tank->bullink, bul) == ER)return ER;
	return OK;
}
void PrintBullet(Bullet bul){
	GotoXy(2 * bul.x, bul.y);
	printf("��");
}
void ClearBullet(Bullet bul){
	GotoXy(2 * bul.x, bul.y);
	printf("  ");
}
Status canPutBullet(Bullet bul, Map map){
	return map.a[bul.y][bul.x];
}
Status canMoveBullet(Bullet bul, Map map){
	//�ж��ӵ��Ƿ��ڱ߽�-gxw
	if (bul.x < 1 || bul.x == (map.length - 2) || bul.y < 1 || bul.y == (map.length - 2))
	{
		return ER;
	}
	switch (bul.dir){
	case 'a':bul.x--; break;
	case 'd':bul.x++; break;
	case 'w':bul.y--; break;
	case 's':bul.y++; break;
	}
	return canPutBullet(bul, map);
}
int isBulletInTank(Bullet bul, Tank tank){
	if (bul.x > tank.x - 2 && bul.x<tank.x + 2 && bul.y>tank.y - 2 && bul.y < tank.y + 2)
		return true;
	else return false;
}
int MoveBullet(Bullet *bul, Tank *tank, Map *map){
	int type;
	type = canMoveBullet(*bul, *map);
	if (isBulletInTank(*bul, *tank) == false)ClearBullet(*bul);
	if (type == 0){
		switch (bul->dir){
		case 'a':bul->x--; break;
		case 'd':bul->x++; break;
		case 'w':bul->y--; break;
		case 's':bul->y++; break;
		}
		PrintBullet(*bul);
	}
	else if (type == 1){
		if (DeleteBullet(tank->bullink, bul) == ER)return ER;
	}
	else if (type == 2 || type == 3){
		switch (bul->dir){
		case 'a':bul->x--; break;
		case 'd':bul->x++; break;
		case 'w':bul->y--; break;
		case 's':bul->y++; break;
		}
		map->a[bul->y][bul->x] = 0;
		ClearBullet(*bul);
		if (DeleteBullet(tank->bullink, bul) == ER)return ER;
	}
	else if (type == ER)
	{
		ClearBullet(*bul);
		if (DeleteBullet(tank->bullink, bul) == ER) return ER;
	}
	return OK;
}
Status MoveTankBullet(Tank *tank, Map *map){
	Bullet *bul;
	Bullet *pre_bul;
	pre_bul = tank->bullink;
	for (bul = tank->bullink->next; bul; bul = bul->next){
		if (MoveBullet(bul, tank, map) == ER)return ER;
		if (pre_bul->next != bul)
		{
			bul = pre_bul;
		}
		else
			pre_bul = bul;
	}
	return OK;
}
Status InitTankLink(Tanklink *tanklink){
	if (tanklink == NULL)return ER;
	tanklink->tank_num = 0;
	tanklink->tanklink = (Tanknode*)malloc(sizeof(Tanknode));
	tanklink->tanklink->tank = NULL;
	tanklink->tanklink->next = NULL;
	return OK;
}
Status DestroyTankLink(Tanklink *tanklink){
	Tanknode *ptr;
	Tanknode *temp;
	if (tanklink == NULL)return ER;
	ptr = tanklink->tanklink;
	while (ptr){
		temp = ptr;
		ptr = ptr->next;
		if (DestroyTank(&temp->tank) == ER)return ER;
		free(temp);
	}
	tanklink->tanklink = NULL;
	tanklink->tank_num = 0;
	return OK;
}
Status ClearTankLink(Tanklink *tanklink){
	Tanknode *ptr;
	Tanknode *temp;
	if (tanklink == NULL || tanklink->tanklink == NULL)return ER;
	ptr = tanklink->tanklink->next;
	while (ptr){
		temp = ptr;
		ptr = ptr->next;
		if (DestroyTank(&temp->tank) == ER)return ER;
		free(temp);
	}
	tanklink->tanklink->next = NULL;
	tanklink->tank_num = 0;
	return OK;
}
Status DeleteTank(Tanklink *tanklink, Tank **tank){
	Tanknode *node;
	Tanknode *del;
	if (!tanklink || !tank)return ER;
	if (!tanklink->tanklink)return ER;
	for (node = tanklink->tanklink; node->next && node->next->tank != *tank; node = node->next);
	if (node->next == NULL)return ER;
	else{
		del = node->next;
		node->next = del->next;
		if (DestroyTank(tank) == ER)return ER;
		free(del);
		tanklink->tank_num--;
		return OK;
	}
}
Status InsertTank(Tanklink *tanklink, Tank *tank){
	Tanknode *node;
	Tanknode *newnode;
	if (!tanklink || !tank)return ER;
	if (!tanklink->tanklink)return ER;
	newnode = (Tanknode*)malloc(sizeof(Tanknode));
	newnode->tank = tank;
	newnode->next = NULL;
	for (node = tanklink->tanklink; node->next; node = node->next);
	node->next = newnode;
	tanklink->tank_num++;
	return OK;
}
Status TankLinkTraverse(Tanklink tlink, void(*visit)(Tank)){
	Tanknode *node;
	if (tlink.tanklink == NULL)return ER;
	for (node = (tlink.tanklink)->next; node; node = node->next){
		visit(*(node->tank));
	}
	return OK;
}
void PrintMainMenu(){
	printf("+-----------------------------+\n");
	printf("|                             |\n");
	printf("|         ̹ �� �� ս         |\n");
	printf("|                             |\n");
	printf("|         1.��ʼ��Ϸ          |\n");
	printf("|         2.��    ��          |\n");
	printf("|         3.��    ��          |\n");
	printf("|         4.��    ��          |\n");
	printf("|         0.��    ��          |\n");
	printf("+-----------------------------+\n");
}
void PrintHelp(){
	printf("+----------------------------+\n");
	printf("|                            |\n");
	printf("|        �� Ϸ �� ��         |\n");
	printf("|     w                      |\n");
	printf("|   a s d     Ϊ�����       |\n");
	printf("|p��Ϊ��ͣ����ͣ����������� |\n");
	printf("|q���˳�(�벻Ҫǿ���˳�������|\n");
	printf("|���ͷ���Ϸ�������ڴ�)     |\n");
	printf("|         ���������         |\n");
	printf("+----------------------------+\n");
	getch();
}
void PrintAbout(){
	printf("+----------------------------+\n");
	printf("|                            |\n");
	printf("|        ��       ��         |\n");
	printf("|                            |\n");
	printf("|               	          |\n");
	printf("|        ���ߣ�����		  |\n");
	printf("|        �汾��1.0	          |\n");
	printf("|                            |\n");
	printf("|        ���������          |\n");
	printf("+----------------------------+\n");
}
int MainMenu(){
	int choice;
	do{
		system("cls");
		PrintMainMenu();
		choice = getch();
	} while (choice<'0' || choice >'4');
	return choice;
}
Status AutoTank(Tank *tank, Map *map){
	int ran;
	char dir;
	if (rand() % 100 < BIU){
		if (CreatBullet(tank) == ER)return ER;
		do{
			ran = rand() % 4;
			switch (ran){
			case 0:dir = 'a'; break;
			case 1:dir = 's'; break;
			case 2:dir = 'd'; break;
			case 3:dir = 'w'; break;
			}
		} while (ChangeTankDir(tank, *map, dir) == ER);
	}
	if (canMoveTank(*tank, *map) == false){
		do{
			ran = rand() % 4;
			switch (ran){
			case 0:dir = 'a'; break;
			case 1:dir = 's'; break;
			case 2:dir = 'd'; break;
			case 3:dir = 'w'; break;
			}
		} while (ChangeTankDir(tank, *map, dir) == ER);
	}
	else{
		ran = rand() % 100;
		if (ran < STRAIGHT){
			MoveTank(tank, *map);
		}
		else{
			do{
				ran = rand() % 4;
				switch (ran){
				case 0:dir = 'a'; break;
				case 1:dir = 's'; break;
				case 2:dir = 'd'; break;
				case 3:dir = 'w'; break;
				}
			} while (ChangeTankDir(tank, *map, dir) == ER);
		}
	}
	MoveTankBullet(tank, map);
	return OK;
}

int main(){
	int x, y;
	int keypress;
	int iterator_bul;
	int choice;
	Tank *tank;
	Tanknode *node;
	Map map;
	Tanklink tlink;
	srand((int)time(NULL));
	InitMap(&map, "map2.map");	//��ʼ����ͼ
	InitTankLink(&tlink);		//��ʼ��̹�˶���
	InitTank(&tank, 2, 15, 'w');	//��ʼ��̹��
	InsertTank(&tlink, tank);
	InitTank(&tank, 2, 2, 's');	//��ʼ��̹��
	InsertTank(&tlink, tank);
	PrintMap(map);				//��ӡ��ͼ
	HideCursor();
	if (TankLinkTraverse(tlink, PrintTank) == ER)printf("error\n");
	iterator_bul = 0;
	getch();
	while (1){
		for (node = tlink.tanklink->next; node; node = node->next)AutoTank(node->tank, &map);
		Sleep(100);
	}
	// while(1){
	// 	if(kbhit()){			//����м�������
	// 		keypress=getch();	//���������AaWwSsDd������һ������ı䷽��
	// 		if(tolower(keypress) == 'a' || tolower(keypress) == 'd' ||
	// 		   tolower(keypress) == 'w' || tolower(keypress) == 's'){
	// 			if(ChangeTankDir(tank,map,tolower(keypress)) == ER)
	// 				MoveTank(tank,map);
	// 		}else if(keypress == ' '){	//�������ո�����һö�ӵ�
	// 			if(CreatBullet(tank) == ER)printf("errror\n");
	// 		}
	// 	}else{
	// 		if(BulletNum(tank->bullink) && iterator_bul >= SPEED_BULLET){
	// 			iterator_bul=0;
	// 			if(MoveTankBullet(tank,&map) == ER)printf("error\n");;
	// 		}
	// 	}
	// 	iterator_bul++;
	// }
	return 0;
}
#else
int main()
{
	FILE *fp;
	fp = fopen("map2.map","w");
	fputs("30\n", fp);
	for (int i = 0; i < 900; ++ i)
	{
		//int ran = rand() % 4;
		fprintf(fp, "%d", 0);
		fprintf(fp, " ");
	}
	fclose(fp);

	return 1;
}
#endif