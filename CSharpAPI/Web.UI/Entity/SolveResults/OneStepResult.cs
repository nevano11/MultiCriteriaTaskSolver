namespace Web.UI.Entity.SolveResults;

public class OneStepResult
{
    public List<SolveInformation> solveInformation { get; }
    
    public OneStepResult(List<SolveInformation> solveInformation)
    {
        this.solveInformation = solveInformation;
    }
}