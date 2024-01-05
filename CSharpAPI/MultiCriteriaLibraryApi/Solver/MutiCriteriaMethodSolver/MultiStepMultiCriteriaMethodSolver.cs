namespace MultiCriteriaLibraryApi.Solver.MutiCriteriaMethodSolver;

using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.DecisionMakingMethod;
using MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;
using MultiCriteriaLibraryApi.DecisionMakingMethod.DecisionMakerInfo;
using MultiCriteriaLibraryApi.DecisionMakingMethod.IntermediateMethodData;
using MultiCriteriaLibraryApi.MathModelComponents;

public class MultiStepMultiCriteriaMethodSolver : IMultiCriteriaMethodSolver
{
    internal IntPtr _solver;
    IntPtr ISolver.getIntPtr() => 
        _solver;

    public AbstractMultiStepMethod MultiStepMethod
    {
        set => MultiStepMultiCriteriaMethodSolver_setMethod(_solver, value.getPtr());
    }

    public MultiStepMultiCriteriaMethodSolver(MathModel mathModel, ICriteriaRelation relation)
    {
        _solver = MultiStepMultiCriteriaMethodSolver_new(mathModel._mathModelPtr, relation.getPtr());
    }

    ~MultiStepMultiCriteriaMethodSolver()
    {
        // MultiStepMultiCriteriaMethodSolver_delete(_solver);
    }

    public Tuple<MathModel, SolveStatus> MakeIteration(IDecisionMakerInfo decisionMakerInfo)
    {
        MultiStepMultiCriteriaMethodSolver_makeIteration(_solver, decisionMakerInfo.GetPtr());
        var mathModel = new MathModel(MultiStepMultiCriteriaMethodSolver_getMethodMathModel(_solver));
        var solveStatus = new SolveStatus(MultiStepMultiCriteriaMethodSolver_getCurrentSolveStatus(_solver));
        return new Tuple<MathModel, SolveStatus>(mathModel, solveStatus);
    }

    public AbstractIntermediateMethodData GetMethodData()
    {
        return new SuccessiveConcessionsIntermediateData(MultiStepMultiCriteriaMethodSolver_getMethodData(_solver));
    }

    public void SolveWithProtocol(string protocolName)
    {
        IntPtr filePtr = Marshal.StringToHGlobalAnsi(protocolName);
        MultiStepMultiCriteriaMethodSolver_solveWithProtocol(_solver, filePtr, protocolName.Length);
        // Marshal.FreeHGlobal(filePtr);
    }
    
    public void MakeIterationWithProtocol(IDecisionMakerInfo decisionMakerInfo, string protocolName)
    {
        IntPtr filePtr = Marshal.StringToHGlobalAnsi(protocolName);
        try
        {
            MultiStepMultiCriteriaMethodSolver_makeIterationWithProtocol(_solver, decisionMakerInfo.GetPtr(), filePtr, protocolName.Length);
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
        Marshal.FreeHGlobal(filePtr);
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MultiStepMultiCriteriaMethodSolver_new(IntPtr mathModel, IntPtr relation);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MultiStepMultiCriteriaMethodSolver_delete(IntPtr solver);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MultiStepMultiCriteriaMethodSolver_setMethod(IntPtr solver, IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MultiStepMultiCriteriaMethodSolver_getCurrentSolveStatus(IntPtr solver);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MultiStepMultiCriteriaMethodSolver_getMethodMathModel(IntPtr solver);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MultiStepMultiCriteriaMethodSolver_makeIteration(IntPtr solver, IntPtr makerInfo);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MultiStepMultiCriteriaMethodSolver_getMethodData(IntPtr solver);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MultiStepMultiCriteriaMethodSolver_makeIterationWithProtocol(IntPtr solver, IntPtr makerInfo, IntPtr protocolFileName, int protocolSize);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MultiStepMultiCriteriaMethodSolver_solveWithProtocol(IntPtr solver, IntPtr protocolFileName, int protocolSize);
}