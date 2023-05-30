void fun1(int x){
    printf("%d\n", x);
}


void wrap_fun(int z ,void (*fun)(int))
{
    fun(z);
}