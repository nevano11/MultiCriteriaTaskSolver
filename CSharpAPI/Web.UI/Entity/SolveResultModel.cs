namespace Web.UI.Entity;

using MultiCriteriaLibraryApi.Solver.MutiCriteriaMethodSolver;

public class SolveResultModel
{
    public bool IsOneStep { get; set; }
    public OneStepMultiCriteriaMethodSolver OSSolver { get; set; }
    public MultiStepMultiCriteriaMethodSolver MSSolver { get; set; }
}