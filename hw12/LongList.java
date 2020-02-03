class LongList implements MyList{
    private LongList next;
    private long data;
     

    public LongList(long data){
        this.next=null;
    }

    public LongList(LongList n, long data){
        this.data=data;
        this.next=n;
    }
    public long getData(){
        return data;
    }
    public LongList next(){
        return next;
    }
    public void printNode(){
        System.out.print("LongList Node, data is: "+this.data);
        if(this.next==null){
            System.out.println();
        }
    }
}