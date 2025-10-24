# List of required packages
packages <- c(
  "tidyverse",    # data manipulation & visualization
  "lubridate",    # date/time handling
  "ggplot2",      # plotting
  "tidytext",     # text mining / sentiment analysis
  "textdata",     # sentiment lexicons
  "randomForest", # machine learning
  "caret",        # ML workflow & metrics
  "prophet",      # time series forecasting
  "zoo"           # time series utilities
)

# Install missing packages
installed <- packages %in% rownames(installed.packages())
if(any(!installed)) {
  install.packages(packages[!installed])
}

# Load all packages
lapply(packages, library, character.only = TRUE)

# Load libraries
library(tidyverse)
library(lubridate)
library(tidytext)
library(textdata)
library(randomForest)
library(caret)
library(prophet)
library(zoo)

# 1. Read dataset
fb <- read_csv("facebook_data.csv",
               col_types = cols(
                 Post_ID = col_integer(),
                 Post_Date = col_date(format="%Y-%m-%d"),
                 Type = col_character(),
                 Category = col_character(),
                 Text = col_character(),
                 Post_Length = col_double(),
                 Hashtags_Count = col_integer(),
                 Media = col_character(),
                 Video_Length_sec = col_double(),
                 Likes = col_double(),
                 Love = col_double(),
                 Wow = col_double(),
                 Haha = col_double(),
                 Sad = col_double(),
                 Angry = col_double(),
                 Comments_Count = col_double(),
                 Comments_Text = col_character(),
                 Shares = col_double(),
                 Reach = col_double(),
                 Impressions = col_double(),
                 Clicks = col_double(),
                 CTR = col_double(),
                 CPC = col_double(),
                 Post_Hour = col_integer(),
                 DayOfWeek = col_character(),
                 Paid = col_logical(),
                 Country = col_character(),
                 Language = col_character(),
                 Audience_AgeTopGroup = col_character()
               ))

# 2. Feature engineering
fb <- fb %>%
  mutate(
    Engagement = Likes + Love + Wow + Haha + Sad + Angry + Comments_Count + Shares,
    InteractionRate = Engagement / Reach, # engagement per reach
    Day = wday(Post_Date, label=TRUE, abbr = TRUE),
    IsWeekend = Day %in% c("Sat","Sun"),
    HasMedia = ifelse(Media %in% c("Image","Video"), TRUE, FALSE)
  )

# Quick look
glimpse(fb)
summary(fb)

# 3. Aggregate metrics
daily <- fb %>%
  group_by(Post_Date) %>%
  summarise(
    Posts = n(),
    Total_Engagement = sum(Engagement, na.rm=TRUE),
    Avg_Engagement = mean(Engagement, na.rm=TRUE),
    Total_Reach = sum(Reach, na.rm=TRUE),
    Total_Clicks = sum(Clicks, na.rm=TRUE)
  ) %>% arrange(Post_Date)

# 4. Exploratory plots
# Avg engagement by Type
fb %>%
  group_by(Type) %>%
  summarise(AvgEng = mean(Engagement, na.rm=TRUE)) %>%
  ggplot(aes(x=reorder(Type, AvgEng), y=AvgEng)) +
  geom_col() +
  coord_flip() +
  labs(title="Average Engagement by Post Type", x="", y="Avg Engagement") +
  theme_minimal()

# Engagement over time
ggplot(daily, aes(x=Post_Date, y=Total_Engagement)) +
  geom_line(size=1) +
  geom_point() +
  labs(title="Total Engagement over Time", x="Date", y="Total Engagement") +
  theme_light()

# Engagement distribution by Category
ggplot(fb, aes(x=Category, y=Engagement)) +
  geom_boxplot() +
  labs(title="Engagement distribution by Category", x="Category", y="Engagement")

# Hour & Day heatmap of average engagement
hour_day <- fb %>%
  group_by(Post_Hour, DayOfWeek) %>%
  summarise(AvgEng = mean(Engagement, na.rm=TRUE)) %>% ungroup()

ggplot(hour_day, aes(x=factor(Post_Hour), y=factor(DayOfWeek, levels=c("Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday")), fill=AvgEng)) +
  geom_tile() +
  labs(title="Avg Engagement by Hour and DayOfWeek", x="Hour", y="DayOfWeek") +
  theme_minimal()

# 5. Sentiment analysis on Comments_Text + Post Text
# Prepare a combined text field
text_df <- fb %>%
  select(Post_ID, Text, Comments_Text) %>%
  mutate(Combined = paste(Text, Comments_Text, sep = " ")) %>%
  select(Post_ID, Combined) %>%
  unnest_tokens(word, Combined)

# Use NRC lexicon (or bing)
nrc <- get_sentiments("nrc")

sentiment_by_post <- text_df %>%
  inner_join(nrc, by = "word") %>%
  count(Post_ID, sentiment) %>%
  pivot_wider(names_from = sentiment, values_from = n, values_fill = 0)

# Join back to fb
fb_sent <- fb %>% left_join(sentiment_by_post, by = "Post_ID")

# Example: plot positive vs negative (bing)
bing <- get_sentiments("bing")
bing_sent <- text_df %>%
  inner_join(bing, by = "word") %>%
  count(Post_ID, sentiment) %>%
  pivot_wider(names_from=sentiment, values_from=n, values_fill=0) %>%
  mutate(net_sentiment = positive - negative)

fb <- left_join(fb, bing_sent, by="Post_ID")

# 6. Build a simple predictive model: predict Engagement bucket (High/Low)
fb_model <- fb %>%
  mutate(Engagement_Label = ifelse(Engagement >= median(Engagement, na.rm=TRUE), "High","Low")) %>%
  select(Engagement_Label, Type, Category, Post_Length, Hashtags_Count, Video_Length_sec, Shares, Reach, Impressions, Clicks, CTR, CPC, Post_Hour, Paid, HasMedia)

# Preprocess: convert factors
fb_model <- fb_model %>%
  mutate_if(is.character, as.factor) %>%
  mutate(Paid = as.factor(Paid))

# Remove rows with NA
fb_model <- na.omit(fb_model)

set.seed(123)
trainIndex <- createDataPartition(fb_model$Engagement_Label, p = .8, list = FALSE)
train <- fb_model[trainIndex, ]
test  <- fb_model[-trainIndex, ]

rf <- randomForest(Engagement_Label ~ ., data=train, ntree=200, importance=TRUE)
print(rf)
varImpPlot(rf)

pred <- predict(rf, test)
confusionMatrix(pred, test$Engagement_Label)

# 7. Time-series forecasting (daily total engagement) using Prophet
prophet_df <- daily %>% select(ds = Post_Date, y = Total_Engagement)
m <- prophet(prophet_df)
future <- make_future_dataframe(m, periods = 30) # forecast next 30 days
forecast <- predict(m, future)
plot(m, forecast) # built-in prophet plot
prophet_plot_components(m, forecast)

# 8. Simple recommendations (printed to console)
# Best post type
best_type <- fb %>% group_by(Type) %>% summarise(avg_eng = mean(Engagement,na.rm=TRUE)) %>% arrange(desc(avg_eng)) %>% slice(1)
cat("Best performing post type:", best_type$Type, "with avg engagement", best_type$avg_eng, "\n")

# Best posting hour
best_hour <- fb %>% group_by(Post_Hour) %>% summarise(avg_eng = mean(Engagement,na.rm=TRUE)) %>% arrange(desc(avg_eng)) %>% slice(1)
cat("Best posting hour:", best_hour$Post_Hour, "with avg engagement", best_hour$avg_eng, "\n")
