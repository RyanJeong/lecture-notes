/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;

    /* reusing 'x' and 'y' as both parameter and member names emphasizes the
     * mapping */
    temp.x = x;
    temp.y = y;

    return temp;
}
