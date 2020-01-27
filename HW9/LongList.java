public class LongList implements MyList{ 
    long data;
    LongList next;
   
    public LongList(LongList n, long data) {
        n.next=n;
        n.data=data;
    }
    public long getData( ){
        return data;
    }
    public LongList next( ){
        return next;
    }
    public void printNode( ){
        System.out.print(next.data);
    }
}