// https://www.dgp.toronto.edu/~patrick/csc418/wi2004/notes/PointersVsRef.pdf
enum day{
    Sunday, Monday, Tuesday 
};

day x;

day &operator++(day &d){
    d = (day)(d + 1);
    return d;
}