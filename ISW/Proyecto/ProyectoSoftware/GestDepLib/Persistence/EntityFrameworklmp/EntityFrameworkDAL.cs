using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Entity;
using System.Threading.Tasks;
using System.Linq.Expressions;

namespace GestDepLib.Persistence
{
   public  class EntityFrameworkDAL :IDAL
    {
        private readonly DbContext dbContext;
        public EntityFrameworkDAL(DbContext dbContext)
        {
            this.dbContext = dbContext;
        }
        public void Insert<T>(T entity) where T : class
        {
            dbContext.Set<T>().Add(entity);
        }
        public void Delete<T>(T entity) where T : class
        {
            dbContext.Set<T>().Remove(entity);
        }
        public IEnumerable<T> GetAll<T>() where T : class
        {
            return dbContext.Set<T>();
        }
        public T GetById<T>(IComparable id) where T : class
        {
            return dbContext.Set<T>().Find(id);
        }
        public IEnumerable<T> GetWhere<T>(Expression<Func<T, bool>> query) where T : class
        {
            return dbContext.Set<T>().Where(query).AsEnumerable();
        }
        public bool Exists<T>(IComparable id) where T : class
        {
            return dbContext.Set<T>().Find(id) != null;
        }
        public void Clear<T>() where T : class
        {
            dbContext.Set<T>().RemoveRange(dbContext.Set<T>());
        }

        public void Commit()
        {
            dbContext.SaveChanges();
        }
    }
}
