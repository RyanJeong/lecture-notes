int data = 12;

int main(void)
{
    int data = 34; /* local variable shadows external `data` */
    return data;   /* after running this app, `echo $?` returns 34 */
}
