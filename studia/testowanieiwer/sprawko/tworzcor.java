
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


