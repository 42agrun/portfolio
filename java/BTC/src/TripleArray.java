public class TripleArray {
    private final int first;
    private final String second;
    private final float third;

    public TripleArray(int a, String b, float c){
        super();
        this.first = a;
        this.second = b;
        this.third = c;
    }

    public int getID(){
        return this.first;
    }

    public String getDate(){ return this.second; }

    public float getValue(){
        return this.third;
    }
}