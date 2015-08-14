import org.junit.Test;
import static org.junit.Assert.*;

public class ChainUnitTests{

  @Test
  public void TestTrivialChain() {
    class displayText{
      String what;

      public displayText(String what){
        this.what = what;
      }
    }
    class TrivialChain extends ChainOfResponsibilites{
      class TrivialWorker implements Worker{
        public final boolean Can(Object in){
          return true;
        }

        public final void Do ( Object in){
          assert (in instanceof displayText);
          System.out.println(((displayText)in).what);

        }

      }
    }


    displayText a = new displayText ("a");
    TrivialChain tc =  new TrivialChain();
    TrivialChain.TrivialWorker tw = tc.new TrivialWorker();
    assertFalse ( tc.Execute(a));
    tc.AddWorker(tw);
    assertTrue ( tc.Execute(a));
  }

  @Test
  public void TestNumChain() {

    class NumChain extends ChainOfResponsibilites{
      class NumWorker implements Worker{

        private int num = 0;

        public final boolean Can(Object in){
          assert (in instanceof Integer);
          if(this.num == (int)in){
            return true;
          }
          return false;
        }

        public NumWorker(int num){
          this.num = num;
        }

        public final void Do ( Object in){
          assert (in instanceof Integer);
          System.out.println(num);

        }

      }
    }
    NumChain nc =  new NumChain();
    assertFalse ( nc.Execute(1));
    for ( int i = 0; i < 1000; i++){
      NumChain.NumWorker nw = nc.new NumWorker(i);
      nc.AddWorker(nw);
    }
    for ( int i = 0; i < 1000; i++){
      assertTrue ( nc.Execute(i));
    }
    assertFalse ( nc.Execute(-1));
    assertFalse ( nc.Execute(1001));
     
    NumChain.NumWorker wrk = nc.new NumWorker(5000);
    nc.RemoveWorker(wrk);

    assertFalse ( nc.Execute(5000));
    nc.AddWorker(wrk);
    assertTrue ( nc.Execute(5000));
    nc.RemoveWorker(wrk);
    assertFalse ( nc.Execute(5000));
    
    for ( int i = 0; i < 1000; i++){
      NumChain.NumWorker nw = nc.new NumWorker(100);
      nc.AddWorker(nw);
    }
    assertTrue ( nc.Execute(100));
    nc.RemoveAllCapableWorkers(100);
    assertTrue( nc.Execute(101));
    

  }

  @Test
  public void StressTest() {

    class NumChain extends ChainOfResponsibilites{
      class NumWorker implements Worker{

        private int num = 0;

        public final boolean Can(Object in){
          assert (in instanceof Integer);
          if(this.num == (int)in){
            return true;
          }
          return false;
        }

        public NumWorker(int num){
          this.num = num;
        }

        public final void Do ( Object in){
          assert (in instanceof Integer);
          System.out.println(num);

        }

      }
    }
    NumChain nc =  new NumChain();
    assertFalse ( nc.Execute(1));
    for ( int i = 0; i < 100000; i++){
      NumChain.NumWorker nw = nc.new NumWorker(i);
      nc.AddWorker(nw);
    }
    for ( int i = 0; i < 1000; i++){
       nc.Execute(100000 - i);
    }

  }
}
