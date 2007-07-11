typedef struct Buffer {
public:
	int **buff;// - указатель
	long len_buff;// - длина динамического массива
	long frequency;// частота выборки
public:
	Buffer(int **buffer, long len_buff, long frequency){
		this->len_buff = len_buff;
		this->frequency = frequency;
		this->buff = (int  **)calloc(this->len_buff,sizeof(int  *));
		for (int i = 0; i < this->len_buff; i ++)
		{
              this->buff[i]=(int *)calloc(2, sizeof(int));
		}
	}
	Buffer(){
		Buffer(NULL, 0, 0);
	}
};