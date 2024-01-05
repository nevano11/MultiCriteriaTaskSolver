using System.Runtime.InteropServices;
using System.Security.Cryptography;

namespace MultiCriteriaLibraryApi.DecisionMakingMethod;

public enum DecisionStatus {
    NONE, //Решение не начато
    PROCESS, //Решение выполняется (ожидается информация от ЛПР)
    OPTIMAL, //Решение найдено оптимальное решение
    FEASIBLE, //Решение окончено, несколько решений
    INFEASIBLE, //Оптимальное решение не найдено
    INVALIDMODEL, //Некорректно задана мат. модель / ограничения
    INVALIDDATA, //Некорректная доп информация для методов
};

public class SolveStatus
{
    internal IntPtr _solveStatusPtr;

    public DecisionStatus DecisionStatus =>
        (DecisionStatus) Enum.Parse(typeof(DecisionStatus), SolveStatus_getDecisionStatus(_solveStatusPtr).ToString());

    public string Message => Marshal.PtrToStringAnsi(SolveStatus_getMessage(_solveStatusPtr));

    public SolveStatus()
    {
        _solveStatusPtr = SolveStatus_new_0();
    }
    
    public SolveStatus(DecisionStatus status)
    {
        _solveStatusPtr = SolveStatus_new_1((int) status);
    }

    public SolveStatus(DecisionStatus status, string message)
    {
        IntPtr messagePtr = Marshal.StringToHGlobalAnsi(message);
        _solveStatusPtr = SolveStatus_new_2((int)status, messagePtr, message.Length);
        Marshal.FreeHGlobal(messagePtr);
    }

    internal SolveStatus(IntPtr solveStatusPtr)
    {
        _solveStatusPtr = solveStatusPtr;
    }

    public override string ToString()
    {
        return $"SolveStatus: decisionStatus={DecisionStatus}, message=\"{Message}\"";
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SolveStatus_new_0();

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SolveStatus_new_1(int decisionStatus);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SolveStatus_new_2(int decisionStatus, IntPtr message, int messageLength);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int SolveStatus_getDecisionStatus(IntPtr solveStatus);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SolveStatus_getMessage(IntPtr solveStatus);
}