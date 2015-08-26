class Config:

  def __init__(self):
    self.numGpu = 8
    self.numL2PerGpu = 4
    self.numCuPerL2 = 4
    self.numGmPerGpu = 4
    self.netConfigFile = "net-si.ini";
    self.memConfigFile = "mem-si.ini";
    self.l1L2NetworkName = "si-net-l1-l2"
    self.l2GmNetworkName = "si-net-l2-gm"

    self.l1BlockSize = 64;
    self.l1Assoc = 4;
    self.l1Size = 64 * 64 * 4;
    self.l1Latency = 1;

    self.l2BlockSize = 64;
    self.l2Assoc = 16;
    self.l2Size = 64 * 64 * 4;
    self.l2Latency = 10;

    self.gmBlockSize = 64;
    self.gmAssoc = 32;
    self.gmSize = 2 ** 28;
    self.gmLatency = 30;


class MemoryConfigGenerator:

  def __init__(self, config):
    self.config = config
    self.configFile = open(config.memConfigFile, 'w')

  def generateGeometry(self):
    l1Sets = config.l1Size / config.l1Assoc / config.l1BlockSize
    self.configFile.write(
        ("[CacheGeometry si-geo-vector-l1]\n"
         "Sets = " + str(l1Sets) + "\n"
         "Assoc = " + str(config.l1Assoc) + "\n"
         "BlockSize = " + str(config.l1BlockSize) + "\n"
         "Latency = " + str(config.l1Latency) + "\n"
         "Policy = LRU\n" + 
         "Ports = 2\n"))
    self.configFile.write(
        ("[CacheGeometry si-geo-scalar-l1]\n"
         "Sets = " + str(l1Sets) + "\n"
         "Assoc = " + str(config.l1Assoc) + "\n"
         "BlockSize = " + str(config.l1BlockSize) + "\n"
         "Latency = " + str(config.l1Latency) + "\n"
         "Policy = LRU\n" + 
         "Ports = 2\n"))
    l2Sets = config.l2Size / config.l2Assoc / config.l2BlockSize
    self.configFile.write(
        ("[CacheGeometry si-geo-l2]\n"
         "Sets = " + str(l2Sets) + "\n"
         "Assoc = " + str(config.l2Assoc) + "\n"
         "BlockSize = " + str(config.l2BlockSize) + "\n"
         "Latency = " + str(config.l2Latency) + "\n"
         "Policy = LRU\n"
         "Ports = 2\n"))
    """
    gmSets = config.gmSize / config.gmAssoc / config.gmBlockSize
    self.configFile.write(
        ("[CacheGeometry si-geo-gm]\n"
         "Sets = " + str(gmSets) + "\n"
         "Assoc = " + str(config.gmAssoc) + "\n"
         "BlockSize = " + str(config.gmBlockSize) + "\n"
         "Latency = " + str(config.gmLatency) + "\n"
         "Policy = LRU\n" + 
         "Ports = 4\n"))
    """

  def generate(self):
    self.generateGeometry();

    numL1V = config.numGpu * config.numL2PerGpu * config.numCuPerL2
    numL1S = config.numGpu * config.numL2PerGpu
    numL2 = config.numGpu * config.numL2PerGpu

    # L1 scalar
    for i in range(0, numL1S):
      self.configFile.write(
          ("[Module si-scalar-l1-" + str(i) + "]\n"
           "Type = Cache\n"
           "Geometry = si-geo-scalar-l1\n"
           "LowNetwork = si-net-l1-l2\n"
           "LowNetworkNode = l1s" + str(i) + "\n"
           "LowModules = l2n" + str(i) + "\n"))

    # L1 scalar
    for i in range(0, numL1V):
      self.configFile.write(
          ("[Module si-vector-l1-" + str(i) + "]\n"
           "Type = Cache\n"
           "Geometry = si-geo-vector-l1\n"
           "LowNetwork = si-net-l1-l2\n"
           "LowNetworkNode = l1v" + str(i) + "\n"
           "LowModules = l2n" + str(i/4) + "\n"))

    # CU entries
    for i in range(0, numL1V):
      self.configFile.write(
          ("[Entry si-cu-" + str(i) + "]\n"
           "Arch = SouthernIslands\n"
           "ComputeUnit = " + str(i) + "\n"
           "DataModule = si-vector-l1-" + str(i) + "\n"
           "ConstantDataModule = si-scalar-l1-" + str(i/4) + "\n"))

    # L2
    for i in range(0, numL2):
      self.configFile.write(
          ("[Module l2n" + str(i) + "]\n"
          "Type = Cache\n"
          "Geometry = si-geo-l2\n"
          "HighNetwork = si-net-l1-l2\n"
          "HighNetworkNode = l2n" + str(i) + "\n"
          "LowNetwork = si-net-l2-gm\n"
          "LowNetworkNode = l2n" + str(i) + "\n"
          ))
      self.configFile.write("LowModules = ");
      for j in range(0, numL2):
        self.configFile.write("gm-" + str(j) + " ")
      self.configFile.write("\n")

    # gm
    for i in range(0, numL2):
      self.configFile.write(
          ("\n[Module gm-" + str(i) + "]\n"
           "Type = MainMemory\n"
           "BlockSize = " + str(config.gmBlockSize) + "\n"
           "Latency = " + str(config.gmLatency) + "\n"
           "HighNetwork = si-net-l2-gm\n"
           "HighNetworkNode = gm-" + str(i) + "\n"
           "AddressRange = ADDR DIV " + str(config.gmBlockSize) + ""
           " MOD " + str(numL2) + " EQ " + str(i) + "\n"))
    

class NetworkConfigGenerator:
  
  def __init__(self, config):
    self.config = config
    self.configFile = open(config.netConfigFile, 'w')

  def getNodeNameByBusId(self, busId):
    numL1V = config.numGpu * config.numL2PerGpu * config.numCuPerL2
    numL1S = config.numGpu * config.numL2PerGpu
    numL2 = config.numGpu * config.numL2PerGpu
    if busId >= 0 and busId < numL1V:
      return "l1v" + str(busId)
    elif busId >= numL1V and busId < numL1V + numL1S:
      return "l1s" + str(busId - numL1V)
    elif busId >= numL1V + numL1S and busId < numL1V + numL1S + numL2:
      return "l2n" + str(busId - numL1V - numL1S)
    else:
      print "Invalid busId " + str(busId)
      exit(1)

  def getCpuIdByBusId(self, busId):
    numL1V = config.numGpu * config.numL2PerGpu * config.numCuPerL2
    numL1S = config.numGpu * config.numL2PerGpu
    numL2 = config.numGpu * config.numL2PerGpu
    numCuPerGpu = config.numL2PerGpu * config.numCuPerL2;
    if busId >= 0 and busId < numL1V:
      return busId / numCuPerGpu
    elif busId >= numL1V and busId < numL1V + numL1S:
      return (busId - numL1V) / config.numL2PerGpu
    elif busId >= numL1V + numL1S and busId < numL1V + numL1S + numL2:
      return (busId - numL1V - numL1S) / config.numL2PerGpu
    else:
      print "Invalid busId " + str(busId)
      exit(1)

  def generateL1L2(self):
    # Network global configuration
    self.configFile.write("[Network." + config.l1L2NetworkName + "]\n") 
    self.configFile.write("DefaultInputBufferSize = 4096\n") 
    self.configFile.write("DefaultOutputBufferSize = 4096\n") 
    self.configFile.write("DefaultBandwidth = 32\n") 
    self.configFile.write("DefaultPacketSize = 4\n") 

    # All l1 vector
    numL1V = config.numGpu * config.numL2PerGpu * config.numCuPerL2
    for i in range(0, numL1V):
      self.configFile.write("[Network." + config.l1L2NetworkName 
          + ".Node.l1v" + str(i) + "]\n")
      self.configFile.write("Type = EndNode\n")

    # All l1 scalar
    numL1S = config.numGpu * config.numL2PerGpu
    for i in range(0, numL1S):
      self.configFile.write("[Network." + config.l1L2NetworkName 
          + ".Node.l1s" + str(i) + "]\n")
      self.configFile.write("Type = EndNode\n")

    # All l2
    numL2 = config.numGpu * config.numL2PerGpu
    for i in range(0, numL2):
      self.configFile.write("[Network." + config.l1L2NetworkName 
          + ".Node.l2n" + str(i) + "]\n")
      self.configFile.write("Type = EndNode\n")

    # All bus nodes
    numBus = numL1V + numL1S + numL2;
    for i in range(0, numL1V + numL1S + numL2):
      self.configFile.write("[Network." + config.l1L2NetworkName 
          + ".Node.bus" + str(i) + "]\n")
      self.configFile.write("Type = Bus\n")

    # All links
    numCuPerGpu = config.numL2PerGpu * config.numCuPerL2;
    for xId in range(0, numBus):
      xCpuId = self.getCpuIdByBusId(xId)
      xName = self.getNodeNameByBusId(xId)
      self.configFile.write("[Network." + config.l1L2NetworkName 
          + ".Link." + xName + "-bus" + str(xId) + "]\n")
      self.configFile.write("Type = Unidirectional\n")
      self.configFile.write("Source = " + xName + "\n")
      self.configFile.write("Dest = bus" + str(xId) + "\n" )

      for yId in range(0, numBus):
        yCpuId = self.getCpuIdByBusId(yId)
        if xCpuId != yCpuId: 
          continue;
        if xId == yId:
          continue;
        yName = self.getNodeNameByBusId(yId)
        self.configFile.write("[Network." + config.l1L2NetworkName 
            + ".Link.bus" + str(xId) + "-" + yName + "]\n")
        self.configFile.write("Type = Unidirectional\n")
        self.configFile.write("Source = bus" + str(xId) + "\n")
        self.configFile.write("Dest = " + yName + "\n" )

  def generateL2GmKim(self):
    # Network global configuration
    self.configFile.write("[Network." + config.l2GmNetworkName + "]\n") 
    self.configFile.write("DefaultInputBufferSize = 4096\n") 
    self.configFile.write("DefaultOutputBufferSize = 4096\n") 
    self.configFile.write("DefaultBandwidth = 32\n") 
    self.configFile.write("DefaultPacketSize = 4\n") 

    # L2 caches
    numL2 = config.numGpu * config.numL2PerGpu
    for i in range(0, numL2):
      self.configFile.write("[Network." + config.l2GmNetworkName 
          + ".Node.l2n" + str(i) + "]\n")
      self.configFile.write("Type = EndNode\n")

    # Gm
    numGm = config.numGpu * config.numGmPerGpu
    for i in range(0, numGm):
      self.configFile.write("[Network." + config.l2GmNetworkName 
          + ".Node.gm-" + str(i) + "]\n")
      self.configFile.write("Type = EndNode\n")

    self.configFile.write("[Network." + config.l2GmNetworkName 
        + ".Node.bus]\n");
    self.configFile.write("Type = Bus\n");

    # Switch per device
    for i in range(0, config.numGpu):
      self.configFile.write("[Network." + config.l2GmNetworkName 
          + ".Node.switch" + str(i) + "]\n")
      self.configFile.write("Type = Switch\n")

      for j in range(0, config.numL2PerGpu):
        l2Id = i * config.numL2PerGpu + j
        self.configFile.write("[Network." + config.l2GmNetworkName
            + ".Link.l2n" + str(l2Id) + "-switch" + str(i) + "]\n")
        self.configFile.write("Type = Bidirectional\n")
        self.configFile.write("Source = l2n" + str(l2Id) + "\n")
        self.configFile.write("Dest = switch" + str(i) + "\n" )
        self.configFile.write("[Network." + config.l2GmNetworkName
            + ".Link.gm" + str(l2Id) + "-switch" + str(i) + "]\n")
        self.configFile.write("Type = Bidirectional\n")
        self.configFile.write("Source = gm-" + str(l2Id) + "\n")
        self.configFile.write("Dest = switch" + str(i) + "\n" )


      self.configFile.write("[Network." + config.l2GmNetworkName
          + ".Link.switch" + str(i) + "-bus]\n")
      self.configFile.write("Type = Bidirectional\n")
      self.configFile.write("Source = bus\n")
      self.configFile.write("Dest = switch" + str(i) + "\n" )


  def generate(self):
    self.generateL1L2()
    self.generateL2GmKim()


if __name__ == "__main__":
  config = Config()
  memoryConfigGenerator = MemoryConfigGenerator(config)
  memoryConfigGenerator.generate()
  networkConfigGenerator = NetworkConfigGenerator(config)
  networkConfigGenerator.generate()
