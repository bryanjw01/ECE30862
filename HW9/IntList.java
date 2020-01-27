class IntList implements MyList{
    int data;
    IntList next;
    public IntList(IntList n, int data) {
        n.next=n;
        n.data=data;
    }
    public int getData( ){
        return next.data;
    }
    public IntList next( ){
        return next;
    }
    public void printNode( ){
        System.out.print(next.data);
    }
}