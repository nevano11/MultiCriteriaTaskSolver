using System.Collections;
using Web.UI.Entity.Inner;

namespace Web.UI.Service;

using Web.UI.Entity.SolveResults;

public class MultiStepResultStorage
{
    private List<MultiStepResult> _solvers;

    public MultiStepResultStorage()
    {
        _solvers = new List<MultiStepResult>();
    }
    
    public void addMultiStepResult(MultiStepResult multiStepResult)
    {
        _solvers.Add(multiStepResult);
    }

    public MultiStepResult getMultiStepResult(Guid guid)
    {
        return _solvers.FirstOrDefault(item => item.Guid.Equals(guid));
    }

    public void removeMultiStepResult(MultiStepResult result)
    {
        _solvers.Remove(result);
    }
}