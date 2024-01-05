using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations.WeightCriteriaRelations;
using MultiCriteriaLibraryApi.MathModelComponents;
using MultiCriteriaLibraryApi.MathModelComponents.Components;
using Web.UI.Entity.Inner;
using Web.UI.Models;
using Web.UI.Service;
using MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;
using MultiCriteriaLibraryApi.DecisionMakingMethod.Method;
using MultiCriteriaLibraryApi.DecisionMakingMethod.Method.AggregationOperators;
using MultiCriteriaLibraryApi.MathModelComponents.Converters;
using MultiCriteriaLibraryApi.MathModelComponents.Converters.Normalizers;
using MultiCriteriaLibraryApi.Solver.MutiCriteriaMethodSolver;
using Web.UI.Entity;
using Web.UI.Entity.SolveResults;
using Criteria = MultiCriteriaLibraryApi.MathModelComponents.Components.Criteria;
using InnerCriteria = Web.UI.Entity.Inner.Criteria;

namespace Web.UI.Controllers
{
    using System.Text.Json;
    using System.Xml;
    using Web.UI.Utils;

    public class HomeController : Controller
    {
        private readonly SupportedMethodInfo _supportedMethodInfo;
        private readonly ReferenceInfo<ICriteriaRelation> _criteriaRelationReferenceInfo;
        private readonly ReferenceInfo<AbstractOneStepMethod> _oneStepReferenceInfo;
        private readonly ReferenceInfo<AbstractMultiStepMethod> _multiStepReferenceInfo;
        private readonly ReferenceInfo<AbstractAggregationOperator> _aggregationOperatorReferenceInfo;
        private readonly ReferenceInfo<INormalizer> _normalizerReferenceInfo;
        private readonly MultiStepResultStorage _methodResultStorage;

        public HomeController(
            SupportedMethodInfo supportedMethodInfo,
            ReferenceInfo<ICriteriaRelation> criteriaRelationReferenceInfo,
            ReferenceInfo<AbstractOneStepMethod> oneStepReferenceInfo,
            ReferenceInfo<AbstractMultiStepMethod> multiStepReferenceInfo,
            ReferenceInfo<AbstractAggregationOperator> aggregationOperatorReferenceInfo,
            ReferenceInfo<INormalizer> normalizerReferenceInfo,
            MultiStepResultStorage methodResultStorage)
        {
            _supportedMethodInfo = supportedMethodInfo;
            _criteriaRelationReferenceInfo = criteriaRelationReferenceInfo;
            _oneStepReferenceInfo = oneStepReferenceInfo;
            _multiStepReferenceInfo = multiStepReferenceInfo;
            _aggregationOperatorReferenceInfo = aggregationOperatorReferenceInfo;
            _normalizerReferenceInfo = normalizerReferenceInfo;
            _methodResultStorage = methodResultStorage;
        }

        public IActionResult Index()
        {
            return View();
        }

        [HttpGet("decision-method-info")]
        public IActionResult GetDecisionMethodInfo()
        {
            return Json(_supportedMethodInfo);
        }

        [HttpGet("criteria-relation-info")]
        public IActionResult GetCriteriaRelationInfo()
        {
            return Json(_criteriaRelationReferenceInfo.Values.Keys);
        }

        [HttpPost("export-xml")]
        public IActionResult ExportXml([FromBody] TaskCondition taskCondition)
        {
            var stream = new MemoryStream();
            XmlDocument document = new XmlDocument();
            XmlNode xmlNode = XmlRepositoryUtils.ObjectToXml(document, taskCondition);
            document.AppendChild(xmlNode);
            document.Save(stream);

            stream.Position = 0;
            var a = new FileStreamResult(stream, "text/plain")
            {
                FileDownloadName = "model.xml"
            };
            return a;
        }
        
        [HttpPost("export-json")]
        public IActionResult ExportJson([FromBody] TaskCondition taskCondition)
        {
            MemoryStream stream = new MemoryStream();
            JsonSerializer.Serialize(stream, taskCondition);

            stream.Position = 0;
            var a = new FileStreamResult(stream, "text/plain")
            {
                FileDownloadName = "model.json"
            };
            return a;
        }
        
        [HttpPost("import")]
        public IActionResult Import(IFormFile file)
        {
            int nameLength = file.FileName.Length;
            if (file.FileName[(nameLength - 4)..].Equals(".xml"))
            {
                var stream = file.OpenReadStream();
                XmlDocument document = new XmlDocument();
                document.Load(stream);
                TaskCondition taskCondition = XmlRepositoryUtils.XmlNodeToObject<TaskCondition>(document.SelectSingleNode("TaskCondition"),
                    "TaskCondition");
                return Json(taskCondition);
            }

            if (file.FileName[(nameLength - 5)..].Equals(".json"))
            {
                TaskCondition? taskCondition = JsonSerializer.Deserialize<TaskCondition>(file.OpenReadStream());
                return Json(taskCondition);
            }
            
            return Json(new TaskCondition());
        }

        [HttpPost("solve-task")]
        public IActionResult SolveTask([FromBody] TaskCondition taskCondition)
        {
            if (taskCondition.CriteriaList.Length == 0 ||
                taskCondition.AlternativeList.Length == 0 ||
                taskCondition.CriteriaRelation == null ||
                taskCondition.MethodInfo == null
               )
                return PartialView("_FieldsDontFilled");

            var mathModel = getMathModelFromUiObjects(taskCondition.CriteriaList, taskCondition.AlternativeList,
                out Dictionary<string, int> criteriaIdMap);
            var criteriaRelation = getCriteriaRelationFromUiObject(taskCondition.CriteriaRelation, criteriaIdMap);

            List<SolveInformation> solveInformation = new List<SolveInformation>();

            switch (taskCondition.MethodInfo.Type)
            {
                case "1":
                    var oSSolver = new OneStepMultiCriteriaMethodSolver(mathModel, criteriaRelation);

                    Dictionary<string, Method> protocolsFNs =
                        taskCondition.MethodInfo.Methods
                            .ToDictionary(method => Path.Combine(Guid.NewGuid() + ".txt"));

                    oSSolver.addMethodsWithProtocols(
                        getOneStepMethodsFromUiObject(taskCondition.MethodInfo.Methods),
                        protocolsFNs.Keys.ToArray());

                    oSSolver.solveWithProtocols();
                    foreach (var (filename, method) in protocolsFNs)
                    {
                        solveInformation.Add(new SolveInformation
                        {
                            Method = method,
                            Information = System.IO.File.ReadAllLines(filename).ToList(),
                        });
                        System.IO.File.Delete(filename);
                    }

                    return PartialView("_OneStepSolveResult", new OneStepResult(solveInformation));
                case "2":
                    var mSSolver = new MultiStepMultiCriteriaMethodSolver(mathModel, criteriaRelation);
                    mSSolver.MultiStepMethod = getMultiStepMethodFromUiObject(taskCondition.MethodInfo.Methods[0]);

                    var stepResult = new MultiStepResult(
                        mSSolver,
                        taskCondition.MethodInfo.Methods[0]
                    );
                    _methodResultStorage.addMultiStepResult(stepResult);
                    if (taskCondition.MethodInfo.Methods.Length > 0)
                        return PartialView("_SuccessiveConcessionsMethodSolveProcess", stepResult);
                    break;
            }

            return PartialView("_FieldsDontFilled");
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [HttpPost("make-iteration")]
        public IActionResult MakeIteration([FromBody] DecisionMakerInfo makerInfo)
        {
            MultiStepResult multiStepResult = _methodResultStorage.getMultiStepResult(makerInfo.Guid);
            var decisionMakerInfo = DecisionMakerInfoFactory.CreateDecisionMakerInfo(makerInfo);
            List<string> protocol = multiStepResult.MakeIteration(decisionMakerInfo);
            return PartialView("_ProtocolResult", protocol);
        }
        
        [HttpPost("stop-solving")]
        public IActionResult StopSolving([FromBody] DecisionMakerInfo makerInfo)
        {
            MultiStepResult multiStepResult = _methodResultStorage.getMultiStepResult(makerInfo.Guid);
            _methodResultStorage.removeMultiStepResult(multiStepResult);
            return Json("aboba");
        }

        [HttpGet("is-solving-stopped")]
        public IActionResult IsSolvingStopped([FromQuery] Guid guid)
        {
            MultiStepResult multiStepResult = _methodResultStorage.getMultiStepResult(guid);
            if (multiStepResult == null)
                return Json(true);
            if (multiStepResult.IsSolutionComplete)
                _methodResultStorage.removeMultiStepResult(multiStepResult);
            return Json(multiStepResult.IsSolutionComplete);
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

        private MathModel getMathModelFromUiObjects(InnerCriteria[] criteriaArray, Alternative[] alternatives,
            out Dictionary<string, int> dictionary)
        {
            dictionary = new Dictionary<string, int>();

            CriteriaType StringToCriteriaType(string type) =>
                type == "max" ? CriteriaType.MAXIMIZATION : CriteriaType.MINIMIZATION;

            List<Criteria> criteriaList = new List<Criteria>();
            List<EstimateVector> estimateVectors = new List<EstimateVector>();
            int id = 1;
            foreach (InnerCriteria innerCriteria in criteriaArray)
            {
                dictionary.Add(innerCriteria.Name, id);
                criteriaList.Add(new Criteria(id++, innerCriteria.Name, StringToCriteriaType(innerCriteria.Type)));
            }

            id = 1;
            int criteriaCount = criteriaList.Count;
            foreach (var alternative in alternatives)
            {
                estimateVectors.Add(new EstimateVector(
                    id++,
                    alternative.Name,
                    alternative.Marks,
                    criteriaCount
                ));
            }

            return new MathModel(criteriaList.ToArray(), estimateVectors.ToArray());
        }

        private ICriteriaRelation getCriteriaRelationFromUiObject(CriteriaRelation criteriaRelation,
            Dictionary<string, int> criteriaIdMap)
        {
            CriteriaConstraint toCriteriaConstraint(string criteriaConstraint)
            {
                switch (criteriaConstraint)
                {
                    case ">":
                        return CriteriaConstraint.More;
                    case ">=":
                        return CriteriaConstraint.MoreOrEquivalent;
                    case "<":
                        return CriteriaConstraint.Less;
                    case "<=":
                        return CriteriaConstraint.LessOrEquivalent;
                    default:
                        return CriteriaConstraint.Equivalent;
                }
            }

            Type relationType = _criteriaRelationReferenceInfo.Values[criteriaRelation.Name];
            int criteriaCount = criteriaIdMap.Count;

            if (relationType == typeof(SimpleCriteriaRelation))
            {
                List<TwoCriteriaRelation> relations = new List<TwoCriteriaRelation>();
                foreach (CriteriaInfo criteriaInfo in criteriaRelation.Info)
                {
                    relations.Add(new TwoCriteriaRelation(
                        criteriaIdMap[criteriaInfo.First],
                        toCriteriaConstraint(criteriaInfo.Constraint),
                        criteriaIdMap[criteriaInfo.Second]
                    ));
                }

                return new SimpleCriteriaRelation(relations.ToArray(), criteriaCount);
            }

            if (relationType == typeof(AllCriteriaRelation))
            {
                CriteriaInfo[] criteriaInfos = criteriaRelation.Info.OrderBy(cR => cR.Value).ToArray();
                var idSeq = new List<int>();
                foreach (CriteriaInfo criteriaInfo in criteriaInfos)
                {
                    idSeq.Add(criteriaIdMap[criteriaInfo.CriteriaName]);
                }

                return new AllCriteriaRelation(criteriaCount, idSeq.ToArray());
            }

            if (relationType == typeof(SimpleRankingMethod) || relationType == typeof(ProportionalMethod))
            {
                Dictionary<int, double> map = new Dictionary<int, double>();
                foreach (CriteriaInfo criteriaInfo in criteriaRelation.Info)
                {
                    map.Add(criteriaIdMap[criteriaInfo.CriteriaName], (double)criteriaInfo.Value);
                }

                return relationType == typeof(SimpleRankingMethod)
                    ? new SimpleRankingMethod(criteriaCount, map)
                    : new ProportionalMethod(criteriaCount, map);
            }

            throw new ArgumentException("Информация о важности критериев не поддерживается!");
        }

        private List<AbstractOneStepMethod> getOneStepMethodsFromUiObject(Method[] methods)
        {
            var oneStepMethods = new List<AbstractOneStepMethod>();
            foreach (Method method in methods)
            {
                Type methodType = _oneStepReferenceInfo.Values[method.Name];
                if (methodType == typeof(LexicographicOptimization))
                {
                    oneStepMethods.Add(new LexicographicOptimization());
                }

                if (methodType == typeof(CriteriaAggregationMethod))
                {
                    AbstractAggregationOperator aggregationOperator = null;
                    INormalizer normalizer = null;
                    foreach (AdditionalMethod additionalMethod in method.AdditionalMethods)
                    {
                        if (_aggregationOperatorReferenceInfo.Name.Equals(additionalMethod.Name))
                        {
                            Type type = _aggregationOperatorReferenceInfo.Values[additionalMethod.Value];
                            if (type == typeof(AddictiveAggregationOperator))
                                aggregationOperator = new AddictiveAggregationOperator();
                            if (type == typeof(MultiplicativeAggregationOperator))
                                aggregationOperator = new MultiplicativeAggregationOperator();
                            if (type == typeof(IdealDistanceAggregationOperator))
                                aggregationOperator = new IdealDistanceAggregationOperator();
                        }

                        if (_normalizerReferenceInfo.Name.Equals(additionalMethod.Name))
                        {
                            Type type = _normalizerReferenceInfo.Values[additionalMethod.Value];
                            if (type == typeof(MinMaxNormalizer))
                                normalizer = new MinMaxNormalizer();
                        }
                    }

                    oneStepMethods.Add(new CriteriaAggregationMethod(aggregationOperator, normalizer));
                }
            }

            return oneStepMethods;
        }

        private AbstractMultiStepMethod getMultiStepMethodFromUiObject(Method method)
        {
            Type methodType = _multiStepReferenceInfo.Values[method.Name];
            AbstractMultiStepMethod resultMethod = null;

            if (methodType == typeof(SuccessiveConcessionsMethod))
            {
                resultMethod = new SuccessiveConcessionsMethod();
            }

            return resultMethod;
        }
    }
}