namespace MultiCriteriaLibraryApi.Solver.MutiCriteriaMethodSolver;

using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.DecisionMakingMethod;
using MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;
using MultiCriteriaLibraryApi.MathModelComponents;

public class OneStepMultiCriteriaMethodSolver : IMultiCriteriaMethodSolver
{
    internal IntPtr _solver;
    IntPtr ISolver.getIntPtr() => _solver;

    public OneStepMultiCriteriaMethodSolver(MathModel mathModel, ICriteriaRelation relation)
    {
        _solver = OneStepMultiCriteriaMethodSolver_new(mathModel._mathModelPtr, relation.getPtr());
    }

    ~OneStepMultiCriteriaMethodSolver()
    {
        OneStepMultiCriteriaMethodSolver_delete(_solver);
    }

    public void addMethod(AbstractOneStepMethod method)
    {
        OneStepMultiCriteriaMethodSolver_addMethod(_solver, method.getPtr());
    }
    
    public void addMethods(List<AbstractOneStepMethod> methods)
    {
        var methodPtrs = methods.Select(m => m.getPtr()).ToArray();
        OneStepMultiCriteriaMethodSolver_addMethods(_solver, ConvertToIntPtr(methodPtrs), methods.Count);
    }
    
    public void addMethodsWithProtocols(List<AbstractOneStepMethod> methods, string[] protocolFileNames)
    {
        var methodPtrs = methods.Select(m => m.getPtr()).ToArray();

        IntPtr[] protocolsPtr = protocolFileNames.Select(Marshal.StringToHGlobalAnsi).ToArray();
        
        int size = protocolFileNames.Length * sizeof(int);
        IntPtr marksPtr = Marshal.AllocHGlobal(size);
        Marshal.Copy(protocolFileNames.Select(fn => fn.Length).ToArray(), 0, marksPtr, protocolFileNames.Length);
        
        OneStepMultiCriteriaMethodSolver_addMethods_wp(
            _solver, ConvertToIntPtr(methodPtrs), methods.Count, 
            ConvertToIntPtr(protocolsPtr), marksPtr
            );
        
        foreach (IntPtr intPtr in protocolsPtr)
        {
            Marshal.FreeHGlobal(intPtr);
        }
    }

    public Dictionary<MathModel, SolveStatus> solve()
    {
        int size = OneStepMultiCriteriaMethodSolver_solve_Size(_solver);
        IntPtr[] keys = new IntPtr[size];
        Marshal.Copy(OneStepMultiCriteriaMethodSolver_solve_Keys(_solver), keys, 0, size);

        IntPtr[] values = new IntPtr[size];
        Marshal.Copy(OneStepMultiCriteriaMethodSolver_solve_Values(_solver), values, 0, size);

        var map = new Dictionary<MathModel, SolveStatus>();
        for (int i = 0; i < size; i++) {
            map.Add(new MathModel(keys[i]), new SolveStatus(values[i]));
        }
        return map;
    }
    
    public void solveWithProtocols()
    {
        OneStepMultiCriteriaMethodSolver_solve_wp(_solver);
    }
    
    private static IntPtr ConvertToIntPtr(IntPtr[] pointers)
    {
        int size = pointers.Length * IntPtr.Size;
        IntPtr ptr = Marshal.AllocHGlobal(size);
        for (int i = 0; i < pointers.Length; i++)
            Marshal.WriteIntPtr(ptr, i * IntPtr.Size, pointers[i]);
        return ptr;
    }

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr OneStepMultiCriteriaMethodSolver_new(IntPtr mathModel, IntPtr relation);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void OneStepMultiCriteriaMethodSolver_delete(IntPtr solver);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void OneStepMultiCriteriaMethodSolver_addMethod(IntPtr solver, IntPtr method);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void OneStepMultiCriteriaMethodSolver_addMethods(IntPtr solver, IntPtr methods, int methodCount);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void OneStepMultiCriteriaMethodSolver_addMethods_wp(
        IntPtr solver, IntPtr methods, int methodCount, 
        IntPtr protocolFileNames, IntPtr protocolLengths);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr OneStepMultiCriteriaMethodSolver_solve_Keys(IntPtr solver);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr OneStepMultiCriteriaMethodSolver_solve_Values(IntPtr solver);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int OneStepMultiCriteriaMethodSolver_solve_Size(IntPtr solver);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void OneStepMultiCriteriaMethodSolver_solve_wp(IntPtr solver);
}