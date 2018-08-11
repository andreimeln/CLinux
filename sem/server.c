

int main(int argc, char *argv[])
{

  struct sembuf sem1;

  key_t key = ftok(SEMNAME); // generates key from text (counts hash)
  if (key < 0)
    {
      fprintf(stderr, "Error creating key\n");
      return 1;
    }
  
  int id = semget(key, 2, 0666 | IPC_CREAT); // 2 sems: serv->cl, cl->serv; key - sem ID
  sem1.sem_num = 0;
  sem1.sem_flg = SEM_UNDO;
  semop(id, &sem1, -1); // -1 - grab this sem

  return 0;
}
