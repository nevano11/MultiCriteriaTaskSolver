using Web.UI.Service;

namespace Web.UI.Entity.SolveResults;

using MultiCriteriaLibraryApi.DecisionMakingMethod.DecisionMakerInfo;
using MultiCriteriaLibraryApi.Solver.MutiCriteriaMethodSolver;
using Web.UI.Entity.Inner;

public class MultiStepResult
{
    public Guid Guid { get; private set; }
    public Method MethodInformation { get; }
    public bool IsSolutionComplete { get; private set; }
    private MultiStepMultiCriteriaMethodSolver Solver;

    public MultiStepResult(
        MultiStepMultiCriteriaMethodSolver solver, 
        Method methodInformation)
    {
        Guid = Guid.NewGuid();
        Solver = solver;
        MethodInformation = methodInformation;
        IsSolutionComplete = false;
    }

    public List<string> Solve()
    {
        var protocolName = Path.Combine(Guid.NewGuid() + ".txt");
        Solver.SolveWithProtocol(protocolName);
        
        var protocol = File.ReadAllLines(protocolName).ToList();
        File.Delete(protocolName);
        if (protocol[^1].Contains("result:"))
            IsSolutionComplete = true;
        return protocol;
    }
    
    public List<string> MakeIteration(IDecisionMakerInfo decisionMakerInfo)
    {
        if (decisionMakerInfo == null)
            return new List<string>();
            
        var protocolName = Path.Combine(Guid + ".txt");
        Solver.MakeIterationWithProtocol(decisionMakerInfo, protocolName);
        
        var protocol = File.ReadAllLines(protocolName).ToList();
        File.Delete(protocolName);
        if (protocol[^1].Contains("result:"))
            IsSolutionComplete = true;
        return protocol;
    }
}