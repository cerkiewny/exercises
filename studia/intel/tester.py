import random

class hmm:
    def __init__(self):
        self.states = []
        self.begprop = []
        self.obsprop = []
        self.prop = []
        self.obs = []

    def add_state(self, name):
        self.states.append(name)
        self.prop.append([])

    def add_obs(self, name):
        self.obs.append(name)
        self.obsprop.append([])

    def initialize(self):
        sums = 0.0
        for a in self.begprop:
            sums += a
        choice = (random.uniform(0, sums))
        i = 0 
        sums = 0.0
        for a in self.begprop:
            sums += a
            if (sums > choice):
                break
            else:
                i+= 1
        self.curstate = self.states[i]
        return (self.curstate)

    def step(self):
        sums = 0.0
        for a in self.prop[self.states.index(self.curstate)]:
            sums += a
        choice = (random.uniform(0, sums))
        i = 0 
        sums = 0.0
        for a in self.prop[self.states.index(self.curstate)]:
            sums += a
            if (sums > choice):
                break
            else:
                i+= 1
        self.curstate = self.states[i]
        return(self.curstate)
    
    def observation(self):
        sums = 0.0
        for a in self.obsprop[self.states.index(self.curstate)]:
            sums += a
        choice = (random.uniform(0, sums))
        i = 0 
        sums = 0.0
        for a in self.obsprop[self.states.index(self.curstate)]:
            sums += a
            if (sums > choice):
                break
            else:
                i+= 1
        return(self.obs[i])

    def add_beg_prop(self, prop):
        self.begprop.append(prop)

    def add_prop(self, state, prop):
        self.prop[state].append(prop)

    def add_obs_prop(self, state, prop):
        self.obsprop[state].append(prop)

numbtests = 40
if __name__ == "__main__":
    hmm = hmm()
    with open('propagation.mat') as f:
        line = f.readline()
        statct = 0
        for stat in line.rstrip("\n\r").split(' '):
            hmm.add_state(stat)
            statct = statct + 1

        line = f.readline()
        for prop in line.rstrip("\n\r").split(' '):
            hmm.add_beg_prop(float(prop));
        
        line = f.readline()
        for a in range(0, statct):
            line = f.readline()
            for prop in line.rstrip("\n\r").split(' '):
                hmm.add_prop(a, float(prop));
        line = f.readline()
        line = f.readline()
        obsc = 0
        for obs in line.rstrip("\n\r").split(' '):
            hmm.add_obs(obs)
            obsc = obsc + 1
        for a in range(0, obsc):
            line = f.readline()
            for obs_prop in line.rstrip("\n\r").split(' '):
                if(obs_prop != ''):
                    hmm.add_obs_prop(a, float(obs_prop));

    test_o = open('hmmtest.out', 'w+')
    test_i = open('hmmtest.in', 'w+')
    test_o.write(hmm.initialize() + '\n')
    test_i.write(hmm.observation() + '\n')
    for a in range (0, numbtests):
        test_o.write(hmm.step() + '\n')
        test_i.write(hmm.observation() + '\n')
    test_o.close()
    test_i.close()
