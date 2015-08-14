import java.util.LinkedList;

abstract class ChainOfResponsibilites{

  static public interface Worker{
    public abstract boolean Can(Object responsibility);
    public abstract void Do(Object responsiblity);
  }
  

  final LinkedList<ChainOfResponsibilites.Worker> Workers;

  ChainOfResponsibilites(){
     Workers = new LinkedList<ChainOfResponsibilites.Worker>();
  }


  public void RemoveWorker(ChainOfResponsibilites.Worker wrk){
    synchronized (Workers) {
      int oldsize = Workers.size();
      if (Workers.contains(wrk)){
        Workers.remove(wrk);
      }
      assert(oldsize - Workers.size() <= 1);
    }
  }

  public void RemoveAllCapableWorkers(Object resp){
    assert (resp != null);
    synchronized (Workers) {
      for(ChainOfResponsibilites.Worker wrk : Workers){
        if(wrk.Can(resp)){
          RemoveWorker(wrk);
          //nasty trick to ommit the modification of iterated collection,
          //because java.
          RemoveAllCapableWorkers(resp);
          break;
        }
      }
    }
  }
  
  public void AddWorker(ChainOfResponsibilites.Worker wrk){
    assert (wrk != null);
    synchronized (Workers) {
      if (!Workers.contains(wrk)){
        Workers.add(wrk);
      }
      assert(Workers.size() > 0 );
    }
  }
  
  public boolean Execute(Object responsibility){
    assert (responsibility != null);
    synchronized (Workers) {
      for(ChainOfResponsibilites.Worker wrk : Workers){
        if(wrk.Can(responsibility)){
          wrk.Do(responsibility);
          return true;
        }
      }
    }
    return false;
  }

}
