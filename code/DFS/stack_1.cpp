typedef struct stack_1
{
    int n;//栈容量
    int top;//栈顶
    int *array; //数组形式的栈
}stack;

int isEmpty(stack *s);//判空
int isfull()
