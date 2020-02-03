class IntList implements MyList{
    private IntList next;
    private int data;
    public IntList(long data){
        this.next=new IntList(n, data);
    }
    public IntList(IntList n, int data){
        this.data=data;
        this.next=n;
        this.next.data=data;
    }
    public int getData(){
        return data;
    }
    public IntList next(){
        return next;
    }
    public void printNode(){
        System.out.print("IntList Node, data is: "+next.data);
    }
}