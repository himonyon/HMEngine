using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace HMEditor.Game.Utilities
{
    public static class Serializer
    {
        public static void ToFIle<T>(T instance, string path)
        {
            try
            {
                using FileStream fs = new FileStream(path, FileMode.Create);
                DataContractSerializer serializer = new DataContractSerializer(typeof(T));
                serializer.WriteObject(fs, instance);
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
                //TODO log error
            }
        }

        internal static T FromFile<T>(string path)
        {
            try
            {
                using FileStream fs = new FileStream(path, FileMode.Open);
                DataContractSerializer serializer = new DataContractSerializer(typeof(T));
                return (T)serializer.ReadObject(fs);
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                //TODO log error
                return default(T);
            }
        }
    }
}
